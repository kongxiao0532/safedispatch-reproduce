echo "entered"
unzip llvmorg-9.0.0.zip
cd llvm-project-llvmorg-9.0.0
mkdir build
cd build
cmake -G 'Unix Makefiles'  -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DCMAKE_BUILD_TYPE=MinSizeRel -LLVM_TARGETS_TO_BUILD=X86 ../llvm
make -j8
make install
export PATH="/root/llvm-project-llvmorg-9.0.0/build/bin:$PATH"
git clone https://github.com/kongxiao0532/safedispatch-reproduce
cd safedispatch-reproduce
