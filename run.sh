export SOURCE=./cpptest/classtest.cpp

# fixed
# safedispatch library
export LIB_SOURCE=./inst-ir/InsLib.cpp
export LIB_BITCODE=InsLib.bc
# bitcode of source code
export SOURCE_BITCODE=source.bc
# instrumented by clang tooling
export INSTRUMENTED_1_SOURCE=./build/instrumented.cpp
# source + library
export MERGE_BITCODE=merge.bc
export MERGE_BITCODE_TEXT=merge.ll
export INSTRUMENTED_BITCODE=instrumented.bc
export INSTRUMENTED_BITCODE_TEXT=instrumented.ll
export BUILD_DIR=./build/

echo 'Building project...'
make
clang -emit-llvm -c ${LIB_SOURCE} -o ${BUILD_DIR}/${LIB_BITCODE}

echo 'Building source code...'
# Clang Tooling (CHA + 1st Instrumentation)
./build/CHATooling ${SOURCE}
# Compile instrumentation library
clang -emit-llvm -c ${INSTRUMENTED_1_SOURCE} -o ${BUILD_DIR}/${SOURCE_BITCODE}
# link instrumented code and library together
llvm-link ${BUILD_DIR}/${LIB_BITCODE} ${BUILD_DIR}/${SOURCE_BITCODE} > ${BUILD_DIR}/${MERGE_BITCODE}
# disassemble bitcode to text for debugging
llvm-dis ${BUILD_DIR}/${MERGE_BITCODE} -o ${BUILD_DIR}/${MERGE_BITCODE_TEXT}
# LLVM pass (2nd Instrumentation)
opt -load build/SafeDispatchIns.so -SafeDispatchIns ${BUILD_DIR}/${MERGE_BITCODE} > ${BUILD_DIR}/${INSTRUMENTED_BITCODE}
# disassemble bitcode to text for debugging
llvm-dis ${BUILD_DIR}/${INSTRUMENTED_BITCODE} -o ${BUILD_DIR}/${INSTRUMENTED_BITCODE_TEXT}