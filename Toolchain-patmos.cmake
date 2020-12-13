set(CMAKE_C_COMPILER patmos-clang)
set(CMAKE_CXX_COMPILER patmos-clang++)
set(UA_ARCHITECTURE "patmos" CACHE STRING "Select architecture patmos,..")

set(PATMOSHOME $ENV{TCRESTHOME}/patmos)
set(LIBETH ${PATMOSHOME}/c/ethlib)
set(SERIAL /dev/ttyUSB0)

