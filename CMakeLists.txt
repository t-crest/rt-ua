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
    set(UA_PATMOS_WCET ON CACHE BOOL "Enable Patmos WCET")
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

# patmos logic analyzer measurment analyze
add_executable(patmos_time_analyze measurment/analyze.c)
set_target_properties(patmos_time_analyze
    PROPERTIES LINK_FLAGS "-O2"
)

add_custom_target(patmos_measurment_analyze
    DEPENDS patmos_time_analyze
    COMMENT "Patmos logic analyzer measurment analyze"
    COMMAND ./patmos_open62541/patmos_time_analyze ../measurment/logic_analyzer_24MHz.csv > ../measurment/wcet_usec.csv
)

# test samples - paper example
add_executable(patmos_test_paper_example_bin test/paper_example.c)
set_target_properties(patmos_test_paper_example_bin
    PROPERTIES LINK_FLAGS "-O0"
)

add_custom_target(patmos_test_paper_example
    DEPENDS patmos_test_paper_example_bin
    COMMENT "Test patmos paper example"
    COMMAND ./patmos_open62541/patmos_test_paper_example_bin
)

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

    # test samples - paper example transformed
    add_executable(patmos_test_paper_example_transform_bin test/paper_example_transform.c)
    set_target_properties(patmos_test_paper_example_transform_bin
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_paper_example_transformed.pml"
    )

    # test samples - recusrion
    add_executable(patmos_test_recursion_bin test/recursion.c)
    set_target_properties(patmos_test_recursion_bin
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_recursion.pml"
    )

    # test samples - jumptable
    add_executable(patmos_test_jumptable_bin test/jumptable.c)
    set_target_properties(patmos_test_jumptable_bin
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_jumptable.pml"
    )

    # test sample - function ptr
    add_executable(patmos_test_function_ptr_bin test/function_ptr.c)
    set_target_properties(patmos_test_function_ptr_bin
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_function_ptr.pml"
    )
    add_executable(patmos_test_function_ptr_void_bin test/function_ptr_void.c)
    set_target_properties(patmos_test_function_ptr_void_bin
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_function_ptr_void.pml"
    )
    add_executable(patmos_test_function_ptr_int_bin test/function_ptr_int.c)
    set_target_properties(patmos_test_function_ptr_int_bin
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_function_ptr_int.pml"
    )

    # test sample - function while loop
    add_executable(patmos_test_while_loop_bin test/while_loop.c)
    set_target_properties(patmos_test_while_loop_bin
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_while_loop.pml"
    )

    # test sample - function for loop
    add_executable(patmos_test_for_loop_bin test/for_loop.c)
    set_target_properties(patmos_test_for_loop_bin
        PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_for_loop.pml"
    )

    add_custom_target(flash
        DEPENDS patmos_open62541
        COMMENT "Build binary for flashing altde2 board"
        COMMAND cd ${PATMOSHOME} && make config BOARD=altde2-all && cd - && sleep 1 && patserdow -v ${SERIAL} patmos_open62541/patmos_open62541
    )
    add_custom_target(copy_ruby_tools
        COMMENT "Copy WCET tools"
        COMMAND cp ../tools/visualize.rb /home/patmos/t-crest/local/lib/platin/tools/visualize.rb && cp ../tools/scopegraph.rb /home/patmos/t-crest/local/lib/platin/analysis/scopegraph.rb
    )
    add_custom_target(wcet
        DEPENDS patmos_open62541_wcet copy_ruby_tools
        COMMENT "Build binary for WCET analysis"
        COMMAND platin wcet -i wcet.pml -b patmos_open62541/patmos_open62541_wcet -e UA_WriterGroup_publishCallback --report
    )
    add_custom_target(analyze
        DEPENDS patmos_open62541_wcet copy_ruby_tools
        COMMENT "Visualize WCET"
        COMMAND platin visualize -i wcet.pml -f UA_WriterGroup_publishCallback --show-calls --show-timings --graphviz-format png -O wcet/
    )
    add_custom_target(patmos_test_paper_example_transform
        DEPENDS patmos_test_paper_example_transform_bin copy_ruby_tools
        COMMENT "Test patmos paper example transformed"
        COMMAND platin wcet -i wcet_paper_example_transformed.pml -b patmos_open62541/patmos_test_paper_example_transform_bin -e calc_pow --report
        #COMMAND platin visualize -i wcet_paper_example_transformed.pml -f calc_pow --show-calls --show-timings --graphviz-format png -O test/
        #COMMAND cd ${PATMOSHOME} && make config BOARD=altde2-all && cd - && sleep 1 && patserdow -v ${SERIAL} patmos_open62541/patmos_test_paper_example_transform_bin
    )
    add_custom_target(patmos_test_recursion
        DEPENDS patmos_test_recursion_bin copy_ruby_tools
        COMMENT "Test patmos recursion"
        COMMAND platin wcet -i wcet_recursion.pml -b patmos_open62541/patmos_test_recursion_bin -e main --report
        #COMMAND platin visualize -i wcet_recursion.pml -f main --show-calls --show-timings --graphviz-format png -O test/
    )
    add_custom_target(patmos_test_jumptable
        DEPENDS patmos_test_jumptable_bin copy_ruby_tools
        COMMENT "Test patmos jumptable"
        COMMAND platin wcet -i wcet_jumptable.pml -b patmos_open62541/patmos_test_jumptable_bin -e jumpTable_test --report
        #COMMAND platin visualize -i wcet_jumptable.pml -f jumpTable_test --show-calls --show-timings --graphviz-format png -O test/
    )
    add_custom_target(patmos_test_function_ptr_callgraph
        DEPENDS patmos_test_function_ptr_bin copy_ruby_tools
        COMMENT "Create patmos function_ptr callgraph"
        COMMAND platin visualize -i wcet_function_ptr.pml -f functionPtr_test --show-calls --show-timings --graphviz-format png -O test/
    )
    add_custom_target(patmos_test_function_ptr_wcet
        DEPENDS patmos_test_function_ptr_bin copy_ruby_tools
        COMMENT "Calculate patmos function_ptr WCET"
        COMMAND platin wcet -i wcet_function_ptr.pml -b patmos_open62541/patmos_test_function_ptr_bin -e functionPtr_test --report
    )
    add_custom_target(patmos_test_function_ptr_void_callgraph
        DEPENDS patmos_test_function_ptr_void_bin copy_ruby_tools
        COMMENT "Create patmos function_ptr_void callgraph"
        COMMAND platin visualize -i wcet_function_ptr_void.pml -f functionPtrVoid_test --show-calls --show-timings --graphviz-format png -O test/
    )
    add_custom_target(patmos_test_function_ptr_void_wcet
        DEPENDS patmos_test_function_ptr_void_bin copy_ruby_tools
        COMMENT "Calculate patmos function_ptr_void WCET"
        COMMAND platin wcet -i wcet_function_ptr_void.pml -b patmos_open62541/patmos_test_function_ptr_void_bin -e functionPtrVoid_test --report
    )
    add_custom_target(patmos_test_function_ptr_int_callgraph
        DEPENDS patmos_test_function_ptr_int_bin copy_ruby_tools
        COMMENT "Create patmos function_ptr_int callgraph"
        COMMAND platin visualize -i wcet_function_ptr_int.pml -f functionPtrInt_test --show-calls --show-timings --graphviz-format png -O test/
    )
    add_custom_target(patmos_test_function_ptr_int_wcet
        DEPENDS patmos_test_function_ptr_int_bin copy_ruby_tools
        COMMENT "Calculate patmos function_ptr_int WCET"
        COMMAND platin wcet -i wcet_function_ptr_int.pml -b patmos_open62541/patmos_test_function_ptr_int_bin -e functionPtrInt_test --report
    )
    add_custom_target(patmos_test_while_loop
        DEPENDS patmos_test_while_loop_bin copy_ruby_tools
        COMMENT "Test patmos while_loop"
        #COMMAND platin wcet -i wcet_while_loop.pml -b patmos_open62541/patmos_test_while_loop_bin -e while_loop_test --report
        #COMMAND platin visualize -i wcet_while_loop.pml -f while_loop_test --show-calls --show-timings --graphviz-format png -O test/
        COMMAND pasim patmos_open62541/patmos_test_while_loop_bin
    )

    add_custom_target(patmos_test_for_loop
        DEPENDS patmos_test_for_loop_bin copy_ruby_tools
        COMMENT "Test patmos for_loop"
        #COMMAND platin wcet -i wcet_for_loop.pml -b patmos_open62541/patmos_test_for_loop_bin -e for_loop_test --report
        COMMAND platin visualize -i wcet_for_loop.pml -f for_loop_test --show-calls --show-timings --graphviz-format png -O test/
        #COMMAND pasim patmos_open62541/patmos_test_for_loop_bin
    )

    add_custom_target(patmos_tests
        DEPENDS patmos_test_function_ptr patmos_test_jumptable patmos_test_recursion patmos_test_while_loop patmos_test_for_loop
        COMMENT "Test patmos function_ptr"
    )

endif()
#file(COPY config.cfg DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
