#cmake .. -DCMAKE_C_COMPILER=/home/patmos/t-crest/local/bin/patmos-clang -DCMAKE_CXX_COMPILER=/home/patmos/t-crest/local/bin/patmos-clang++
# for cross-compiling for Patmos  use the comand "cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-patmos.cmake .."

cmake_minimum_required(VERSION 2.6)


set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Verbose Makefile")

# build open62541
set(OPEN62541_DIR extern/open62541)
set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build" FORCE)
set(UA_ENABLE_AMALGAMATION OFF CACHE BOOL "UA_ENABLE_AMALGAMATION")
set(UA_ENABLE_DA OFF CACHE BOOL "UA_ENABLE_DA")
set(UA_ENABLE_DISCOVERY OFF CACHE BOOL "UA_ENABLE_DISCOVERY")
set(UA_ENABLE_NODEMANAGEMENT OFF CACHE BOOL "UA_ENABLE_NODEMANAGEMENT")
set(UA_ENABLE_PUBSUB ON CACHE BOOL "Enable open62541 PubSub information model")
set(UA_LOGLEVEL 100 CACHE STRING "Set Loglevel 600(FATAL)")
set(UA_NAMESPACE_ZERO MINIMAL CACHE STRING "open62541 namespace zero MINIMAL, REDUCED, FULL")

if("${UA_ARCHITECTURE}" STREQUAL "patmos")
    set(UA_LOGLEVEL 600 CACHE STRING "Set Loglevel 600(FATAL)")
    set(UA_ENABLE_PUBSUB_CUSTOM_PUBLISH_HANDLING ON CACHE BOOL "Enable open62541 PubSub custom publish handling")
endif()

add_subdirectory(${OPEN62541_DIR} open62541)

# build the patmos_open62541 itself
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/patmos_open62541")
set(PATMOS_OPEN62541_SOURCE_FILES
    open62541_patmos.c)

add_executable(patmos_open62541 ${PATMOS_OPEN62541_SOURCE_FILES})
target_link_libraries(patmos_open62541 PUBLIC
    open62541 m)

add_executable(pubsub_subscriber pubsub_subscriber.c)
target_link_libraries(pubsub_subscriber PUBLIC
    open62541 m)

if("${UA_ARCHITECTURE}" STREQUAL "patmos")
    file(GLOB patmos_libeth_src ${LIBETH}/*.c)
    add_library(patmos_libeth ${patmos_libeth_src})
    target_link_libraries(patmos_open62541 PUBLIC patmos_libeth)

    add_executable(patmos_open62541_wcet ${PATMOS_OPEN62541_SOURCE_FILES})
    target_include_directories(patmos_open62541_wcet PUBLIC ~/t-crest/patmos/c/ethlib)
    target_link_libraries(patmos_open62541_wcet PUBLIC
        open62541 m)
    target_link_libraries(patmos_open62541_wcet PUBLIC patmos_libeth)

	#set_target_properties(patmos_open62541 PROPERTIES COMPILE_FLAGS "-target patmos-unknown-unknown-elf -mpatmos-disable-vliw")
    set_target_properties(patmos_open62541
        PROPERTIES LINK_FLAGS "-O2 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet.pml"
    )
    set_target_properties(patmos_open62541_wcet
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet.pml"
    )
    target_include_directories(patmos_open62541 PUBLIC ~/t-crest/patmos/c/ethlib)


    add_custom_target(flash
        DEPENDS patmos_open62541
        COMMENT "Build binary for flashing altde2 board"
        COMMAND cd ${PATMOSHOME} && make config BOARD=altde2-all && cd - && sleep 1 && patserdow -v ${SERIAL} patmos_open62541/patmos_open62541
    )
    add_custom_target(wcet
        DEPENDS patmos_open62541_wcet
        COMMENT "Build binary for WCET analysis"
        COMMAND platin wcet -i wcet.pml -b patmos_open62541/patmos_open62541_wcet -e UA_WriterGroup_publishCallback --report
    )
    add_custom_target(analyze
        DEPENDS wcet
        COMMENT "Visualize WCET "
        COMMAND platin visualize -i wcet.pml -f UA_WriterGroup_publishCallback --show-calls --show-timings --graphviz-format dot -O wcet/
    )

endif()
#file(COPY config.cfg DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"