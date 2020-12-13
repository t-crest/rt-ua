set(CMAKE_C_COMPILER patmos-clang)
set(CMAKE_CXX_COMPILER patmos-clang++)

set(LIBETH ${PATMOSHOME}/c/ethlib)
set(SERIAL /dev/ttyUSB0)

add_definitions( -DUA_PATMOS_WCET )
