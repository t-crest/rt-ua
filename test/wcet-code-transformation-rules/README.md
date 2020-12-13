# rt-UA tests

Contains some small test examples to get familiar with the toolchain and test how WCET analysis behaves for certain small but challenging examples.

### Prerequisites

Download the Patmos Ubuntu Development VM from http://patmos.compute.dtu.dk/ or follow the installation instructions on https://github.com/t-crest/patmos

Add the following lines to your ~/.bashrc

```shell
export PATH=$PATH:$HOME/t-crest/local/bin
export TCRESTHOME=$HOME/t-crest
```

### Build for Patmos

```shell
mkdir build-patmos
cd build-patmos

cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-patmos.cmake ..
```

### Create call graph

```shell
# for the call graph of recursion.c use
make patmos_test_recursion_visualize

```

### 