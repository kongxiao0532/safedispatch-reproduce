# Reproduce of SafeDispatch

SafeDispatch is a series of LLVM passes for C++ vtable protection. It checks the target address of every indirect call in advance to ensure the address is legitimate. [SafeDispatch NDSS '14 Paper](https://homes.cs.washington.edu/~ztatlock/pubs/sd-jang-ndss14.pdf)

This repository implements class pointer protection (ValidM Table) of SafeDispatch in an ad-hoc manner.

This implementation includes two **ASTVistitor**s based on [Clang LibTooling](https://clang.llvm.org/docs/LibTooling.html) and one **pass** on [LLVM IR](https://llvm.org/docs/LangRef.html). All together there are **1,256 LoC (excluding blank lines and comments)**. I believe all comments in the code are easy to read and understand.

## Set up Environment
The code is tested on LLVM version 9.0 with clang & clang-tools-extra.

### Set up environment using docker
```bash
$ cd docker
$ docker build -t ubuntu:safedispatch .
$ docker run -it ubuntu:safedispatch /bin/bash
```

### Set up environment manually
1. Download the LLVM project source code from [[llvm-project 9.0 Source Code Release](https://github.com/llvm/llvm-project/archive/llvmorg-9.0.0.zip)].
   ```bash
   $ wget https://github.com/llvm/llvm-project/archive/llvmorg-9.0.0.zip
   ```
2. Build LLVM with *clang* and *clang-tools-extra* (choose one between *Unix Make* and *Ninja*)
   ```bash
   $ unzip llvmorg-9.0.0.zip
   $ cd llvm-project-llvmorg-9.0.0
   $ mkdir build
   $ cd build
   # Using Unix Make
   $ cmake -G 'Unix Makefiles'  -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" ../llvm
   $ make -jN
   # Using Ninja
   $ cmake -G 'Ninja'  -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" ../llvm
   $ ninja
   ```
3. Install binaries
   ```bash
   $ sudo make install
   $ export PATH="{PATH-TO-LLVM-PROJECT}/build/bin:$PATH"
   ```
4. Download project
   ```bash
    git clone https://github.com/kongxiao0532/safedispatch-reproduce
    cd safedispatch-reproduce
    ```
5. Configure LLVM path in ```./Makefile```
   ```makefile
    LLVM_SRC_PATH := {PATH-TO-LLVM-PROJECT}
   ```

## All-in-one script
An all-in-one script ```./run.sh``` is provided for **building the project** and using it to **compile a C++ program**, so that no extra operations are needed. The C++ program is delared as a argument passed to ```run.sh```.
```bash
$ ./run.sh [xxx.cpp]
```
 The default program is ```./build/classtest.cpp``` which contains a five-class hierachy. The standard output of ```./build/classtest.cpp``` will be as follows.
```shell
$ ./run.sh
Target:  ./cpptest/classtest.cpp

[run.sh]: Building target:  ./cpptest/classtest.cpp  ...
(LLVM&Clang compilation output)

[run.sh]: Building source code... ['file not found' errors are normal for Clang Tooling]
(Clang Tooling output)

[run.sh]: Running  ./cpptest/classtest.cpp :
m1 with no arguments in A
m1 with int argument in A
m2 in A
m3 in A
foo in A
m1 with no arguments in B
m1 with int argument in B
m2 in A
m3 in A
foo in B
m1 in C
m1 with int argument in A
m2 in A
m3 in A
foo in A
m1 in C
m1 with int argument in A
m2 in D
m3 in A
foo in A
m1 in C
m1 with int argument in A
m2 in A
m3 in E
foo in A
m1 with no arguments in B
m1 with int argument in B
m2 in A
m3 in A
foo in B
m1 in C
m2 in A
m3 in A
foo in A
m1 in C
m2 in D
m3 in A
foo in A
m1 in C
m2 in A
m3 in E
foo in A
m1 in C
m2 in D
m3 in A
foo in A
m1 in C
m2 in A
m3 in E
foo in A
```


## Building the project manually
```bash
make
```
The binary file of **the Clang tool** is ```./build/CHAToooling```.

The binary file of **the LLVM pass** is ```./build/CHAToooling```.

> ### Optional:
> #### Enable an advanced version of ValidM
> Modify code in ```./common.h```
> ```cpp
> #define VALIDM_WITH_PARAMS true // enable advanced ValidM
> #define VALIDM_WITH_PARAMS false // disable advanced ValidM
> ```
> #### Enable output for debugging
> Modify code in ```./common.h```
> ```cpp
> #define CUSTOM_DEBUG 0 // enable debug output
> // #define CUSTOM_DEBUG 0 // disable debug output
> ```


## Usage
- Clang LibTooling for class hierachy analysis and instrumentation
  ```bash
  ./build/CHATooling {source_code}
  ```
- LLVM pass for a complete instrumentation
  ```bash
  opt -load build/SafeDispatchIns.so -SafeDispatchIns {input_bitcode} > {output_bitcode}
  ```