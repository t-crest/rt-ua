# rt-ua
Real-Time OPC UA

## Build for Patmos

Patmos Ubuntu VM required: http://patmos.compute.dtu.dk/ 

```shell
git clone  --recursive https://github.com/t-crest/rt-ua

cd rt-ua

mkdir build-patmos
cd build-patmos

cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-patmos.cmake ..
```

## Build for Ubuntu

```shell
git clone  --recursive https://github.com/t-crest/rt-ua

cd rt-ua

mkdir build
cd build

cmake ..
```




