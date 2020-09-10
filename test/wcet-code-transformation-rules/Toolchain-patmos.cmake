set(CMAKE_C_COMPILER /home/patmos/t-crest/local/bin/patmos-clang)
set(CMAKE_CXX_COMPILER /home/patmos/t-crest/local/bin/patmos-clang++)

set(PATMOSHOME /home/patmos/t-crest/patmos)
set(LIBETH ${PATMOSHOME}/c/ethlib)
set(SERIAL /dev/ttyUSB0)

add_definitions( -DUA_PATMOS_WCET )
