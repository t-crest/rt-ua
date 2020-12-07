# rt-ua
Real-Time OPC UA Pub/Sub implementaion using the open62541 library on Patmos.

## Getting Started

### Prerequisites

Download the Patmos Ubuntu Development VM from http://patmos.compute.dtu.dk/

## Installing

Install the Development VM and login with the Username and Password **patmos**. The T-Crest ist split into several Github(https://github.com/t-crest) repositories and can be found under **/home/patmos/t-crest/** on the Development VM.

### Update Patmos Source Code

```shell
cd ~/t-crest/patmos/

git pull
```

### Build for Patmos

```shell
git clone  --recursive https://github.com/t-crest/rt-ua

cd rt-ua

mkdir build-patmos
cd build-patmos

cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-patmos.cmake ..
```

### Build for Ubuntu

```shell
git clone  --recursive https://github.com/t-crest/rt-ua

cd rt-ua

mkdir build
cd build

cmake ..
```

## Test Setup