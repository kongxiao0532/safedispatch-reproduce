echo "entered"
unzip llvmorg-9.0.0.zip
cd llvm-project-llvmorg-9.0.0
mkdir build
cd build
cmake -G 'Unix Makefiles'  -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" ../llvm
make -j8
make install
export PATH="/root/llvm-project-llvmorg-9.0.0/build/bin:$PATH"
git clone https://github.com/kongxiao0532/safedispatch-reproduce
cd safedispatch-reproduce
