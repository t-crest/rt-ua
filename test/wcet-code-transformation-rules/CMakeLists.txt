#cmake .. -DCMAKE_C_COMPILER=/home/patmos/t-crest/local/bin/patmos-clang -DCMAKE_CXX_COMPILER=/home/patmos/t-crest/local/bin/patmos-clang++
# for cross-compiling for Patmos  use the comand "cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-patmos.cmake .."

cmake_minimum_required(VERSION 2.6)

# create subdirectories for the various cmake targets
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/call_graphs)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Verbose Makefile")
set(CALLGRAPH_VISUALIATIONS_TOOLS_SRC_FOLDER "../../../tools")
set(CALLGRAPH_VISUALIATIONS_TOOLS_DST_FOLDER "/home/patmos/t-crest/local/lib/platin/tools")

add_custom_target(copy_ruby_tools
    COMMENT "Copy call graph visualization tools"
    COMMAND cp ${CALLGRAPH_VISUALIATIONS_TOOLS_SRC_FOLDER}/visualize.rb ${CALLGRAPH_VISUALIATIONS_TOOLS_DST_FOLDER}/visualize.rb && cp ${CALLGRAPH_VISUALIATIONS_TOOLS_SRC_FOLDER}/scopegraph.rb ${CALLGRAPH_VISUALIATIONS_TOOLS_DST_FOLDER}/scopegraph.rb
)


# test samples - recursion
add_executable(patmos_test_recursion_bin recursion.c)
set_target_properties(patmos_test_recursion_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_recursion.pml"
)

add_custom_target(patmos_test_recursion_visulize
    DEPENDS patmos_test_recursion_bin copy_ruby_tools
    COMMAND platin visualize -i wcet_recursion.pml -f main --graphviz-format png -O call_graphs
)

add_custom_target(patmos_test_recursion_wcet
    DEPENDS patmos_test_recursion_bin
    COMMAND platin wcet -i wcet_recursion.pml -b patmos_test_recursion_bin -e main --report
)

# test samples - jumptable
add_executable(patmos_test_jumptable_bin jumptable.c)
set_target_properties(patmos_test_jumptable_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_jumptable.pml"
)

add_custom_target(patmos_test_jumptable_visualize
    DEPENDS patmos_test_jumptable_bin copy_ruby_tools
    COMMAND platin visualize -i wcet_jumptable.pml -f jumpTable_test --show-calls --show-timings --graphviz-format png -O call_graphs
)

add_custom_target(patmos_test_jumptable_wcet
    DEPENDS patmos_test_jumptable_bin
    COMMAND platin wcet -i wcet_jumptable.pml -b patmos_test_jumptable_bin -e jumpTable_test --report
)

# test sample - function ptr
add_executable(patmos_test_function_ptr_bin function_ptr.c)
set_target_properties(patmos_test_function_ptr_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_function_ptr.pml"
)

add_custom_target(patmos_test_function_ptr_visualize
    DEPENDS patmos_test_function_ptr_bin copy_ruby_tools
    COMMAND platin visualize -i wcet_function_ptr.pml -f functionPtr_test --show-calls --show-timings --graphviz-format png -O call_graphs
)

add_custom_target(patmos_test_function_ptr_wcet
    DEPENDS patmos_test_function_ptr_bin
    COMMAND platin wcet -i wcet_function_ptr.pml -b patmos_test_function_ptr_bin -e functionPtr_test --report
)

# test sample - function ptr void
add_executable(patmos_test_function_ptr_void_bin function_ptr_void.c)
set_target_properties(patmos_test_function_ptr_void_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_function_ptr_void.pml"
)

add_custom_target(patmos_test_function_ptr_void_visualize
    DEPENDS patmos_test_function_ptr_void_bin copy_ruby_tools
    COMMAND platin visualize -i wcet_function_ptr_void.pml -f functionPtrVoid_test --show-calls --show-timings --graphviz-format png -O call_graphs
)

add_custom_target(patmos_test_function_ptr_void_wcet
    DEPENDS patmos_test_function_ptr_void_bin
    COMMAND platin wcet -i wcet_function_ptr.pml -b patmos_test_function_ptr_void_bin -e functionPtr_test --report
)

# test sample - function ptr int
add_executable(patmos_test_function_ptr_int_bin function_ptr_int.c)
set_target_properties(patmos_test_function_ptr_int_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_function_ptr_int.pml"
)

add_custom_target(patmos_test_function_ptr_int_visualize
    DEPENDS patmos_test_function_ptr_int_bin copy_ruby_tools
    COMMAND platin visualize -i wcet_function_ptr_int.pml -f functionPtrInt_test --show-calls --show-timings --graphviz-format png -O call_graphs
)

add_custom_target(patmos_test_function_ptr_int_wcet
    DEPENDS patmos_test_function_ptr_int_bin
    COMMAND platin wcet -i wcet_function_ptr_int.pml -b patmos_test_function_ptr_int_bin -e functionPtrInt_test --report
)

# test sample - function while loop
add_executable(patmos_test_while_loop_bin while_loop.c)
set_target_properties(patmos_test_while_loop_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_while_loop.pml"
)

# test sample - function for loop
add_executable(patmos_test_for_loop_bin for_loop.c)
set_target_properties(patmos_test_for_loop_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_for_loop.pml"
)

# test samples - paper example original; will not compile for patmos
add_executable(patmos_test_paper_example_original_bin paper_example_original.c)
set_target_properties(patmos_test_paper_example_original_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_paper_example_original.pml"
)

add_custom_target(patmos_test_paper_example_original_visualize
    DEPENDS patmos_test_paper_example_original_bin copy_ruby_tools
    COMMAND platin visualize -i wcet_paper_example_original.pml -f calc_pow --show-calls --show-timings --graphviz-format png -O call_graphs
)

add_custom_target(patmos_test_paper_example_original_wcet
    DEPENDS patmos_test_paper_example_original_bin
    COMMAND platin wcet -i wcet_paper_example_original.pml -b patmos_test_paper_example_original_bin -e calc_pow --report
)

add_custom_target(patmos_test_paper_example_original_flash
    DEPENDS patmos_test_paper_example_original_bin
    COMMAND cd ${PATMOSHOME} && make config BOARD=altde2-all && cd - && sleep 1 && patserdow -v ${SERIAL} patmos_test_paper_example_original_bin
)

# test samples - paper example intermediate (only changes required to generate the call graph have been applied); visualize should be possible but WCET analysis should fail
add_executable(patmos_test_paper_example_intermediate_bin paper_example_intermediate.c)
set_target_properties(patmos_test_paper_example_intermediate_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_paper_example_intermediate.pml"
)

add_custom_target(patmos_test_paper_example_intermediate_visualize
    DEPENDS patmos_test_paper_example_intermediate_bin copy_ruby_tools
    COMMAND platin visualize -i wcet_paper_example_intermediate.pml -f calc_pow --show-calls --show-timings --graphviz-format png -O call_graphs
)

add_custom_target(patmos_test_paper_example_intermediate_wcet
    DEPENDS patmos_test_paper_example_intermediate_bin
    COMMAND platin wcet -i wcet_paper_example_intermediate.pml -b patmos_test_paper_example_intermediate_bin -e calc_pow --report
)

add_custom_target(patmos_test_paper_example_intermediate_flash
    DEPENDS patmos_test_paper_example_intermediate_bin
    COMMAND cd ${PATMOSHOME} && make config BOARD=altde2-all && cd - && sleep 1 && patserdow -v ${SERIAL} patmos_test_paper_example_intermediate_bin
)

# test samples - paper example transformed
add_executable(patmos_test_paper_example_transformed_bin paper_example_transformed.c)
#set_target_properties(patmos_test_paper_example_transformed_bin
#    PROPERTIES COMPILE_FLAGS "-Os"
#)

set_target_properties(patmos_test_paper_example_transformed_bin
    PROPERTIES LINK_FLAGS "-O0 -target patmos-unknown-unknown-elf -mpatmos-disable-vliw -mserialize=wcet_paper_example_transformed.pml"
)

add_custom_target(patmos_test_paper_example_transformed_visualize
    DEPENDS patmos_test_paper_example_transformed_bin copy_ruby_tools
    COMMAND platin visualize -i wcet_paper_example_transformed.pml -f calc_pow --show-calls --show-timings --graphviz-format png -O call_graphs
)

add_custom_target(patmos_test_paper_example_transformed_wcet
    DEPENDS patmos_test_paper_example_transformed_bin
    COMMAND platin wcet -i wcet_paper_example_transformed.pml -b patmos_test_paper_example_transformed_bin -e calc_pow --report
)

add_custom_target(patmos_test_paper_example_transformed_flash
    DEPENDS patmos_test_paper_example_transformed_bin
    COMMAND cd ${PATMOSHOME} && make config BOARD=altde2-all && cd - && sleep 1 && patserdow -v ${SERIAL} patmos_test_paper_example_transformed_bin
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

    add_custom_target(patmos_test_while_loop
        DEPENDS patmos_test_while_loop_bin copy_ruby_tools
        COMMENT "Test patmos while_loop"
        #COMMAND platin wcet -i wcet_while_loop.pml -b patmos_open62541/patmos_test_while_loop_bin -e while_loop_test --report
        #COMMAND platin visualize -i wcet_while_loop.pml -f while_loop_test --show-calls --show-timings --graphviz-format png -O 
        COMMAND pasim patmos_open62541/patmos_test_while_loop_bin
    )

    add_custom_target(patmos_test_for_loop
        DEPENDS patmos_test_for_loop_bin copy_ruby_tools
        COMMENT "Test patmos for_loop"
        #COMMAND platin wcet -i wcet_for_loop.pml -b patmos_open62541/patmos_test_for_loop_bin -e for_loop_test --report
        COMMAND platin visualize -i wcet_for_loop.pml -f for_loop_test --show-calls --show-timings --graphviz-format png -O 
        #COMMAND pasim patmos_open62541/patmos_test_for_loop_bin
    )


endif()
#file(COPY config.cfg DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"