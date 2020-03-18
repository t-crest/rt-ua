# rt-ua
Real-Time OPC UA

## Build for Patmos Ubuntu VM

Patmos Ubuntu VM required: http://patmos.compute.dtu.dk/ 

```shell
git clone  --recursive https://github.com/t-crest/rt-ua

mkdir build
cd build

cmake .. -DCMAKE_C_COMPILER=/home/patmos/t-crest/local/bin/patmos-clang -DCMAKE_CXX_COMPILER=/home/patmos/t-crest/local/bin/patmos-clang++
```



