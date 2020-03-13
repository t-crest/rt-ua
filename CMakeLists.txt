#cmake .. -DCMAKE_C_COMPILER=/home/patmos/t-crest/local/bin/patmos-clang -DCMAKE_CXX_COMPILER=/home/patmos/t-crest/local/bin/patmos-clang++


cmake_minimum_required (VERSION 2.6)

set(PATMOSHOME ~/t-crest/patmos)
set(LIBETH ${PATMOSHOME}/c/ethlib)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Verbose Makefile")

SET(CMAKE_CROSSCOMPILING 1)

option(USE_CLANG "build application with patmos-clang" ON) # ON is the default

if(USE_CLANG)
#    set(CMAKE_C_COMPILER /home/patmos/t-crest/local/bin/patmos-clang)
#    set(CMAKE_CXX_COMPILER /home/patmos/t-crest/local/bin/patmos-clang++)
endif(USE_CLANG)

# build open62541
set(OPEN62541_DIR extern/open62541)
set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build" FORCE)
set(UA_ARCHITECTURE "patmos" CACHE STRING "Select architecture patmos,..")
set(UA_ENABLE_AMALGAMATION OFF CACHE BOOL "UA_ENABLE_AMALGAMATION")
set(UA_ENABLE_DA OFF CACHE BOOL "UA_ENABLE_DA")
set(UA_ENABLE_DISCOVERY OFF CACHE BOOL "UA_ENABLE_DISCOVERY")
set(UA_ENABLE_NODEMANAGEMENT OFF CACHE BOOL "UA_ENABLE_NODEMANAGEMENT")
set(UA_ENABLE_PUBSUB ON CACHE BOOL "Enable open62541 PubSub information model")
set(UA_LOGLEVEL 300 CACHE STRING "Set Loglevel 300")
set(UA_ENABLE_PUBSUB_CUSTOM_PUBLISH_HANDLING ON CACHE BOOL "Enable open62541 PubSub custom publish handling")
#set(UA_NAMESPACE_ZERO MINIMAL CACHE STRING "open62541 namespace zero MINIMAL, REDUCED, FULL")
remove_definitions(-Werror)
add_subdirectory(${OPEN62541_DIR} open62541)


# build the patmos_open62541 itself
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/patmos_open62541")
set(PATMOS_OPEN62541_SOURCE_FILES
    open62541_patmos.c)

add_executable(patmos_open62541 ${PATMOS_OPEN62541_SOURCE_FILES})
target_include_directories(patmos_open62541 PUBLIC
    ${LIBCONFIG_DIR}/lib ${LIBETH})
target_link_libraries(patmos_open62541 PUBLIC
    open62541
    config)
SET_TARGET_PROPERTIES(patmos_open62541 PROPERTIES COMPILE_FLAGS "-target patmos-unknown-unknown-elf -O2")
#file(COPY config.cfg DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
