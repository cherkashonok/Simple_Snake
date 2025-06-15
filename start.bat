if not exist "tmp" (
    mkdir tmp
)

cmake ^
    -S . ^
    -B tmp ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DCMAKE_CXX_COMPILER:PATH="D:\LLVM\bin\clang++.exe" ^
    -DCMAKE_LINKER:PATH="D:\LLVM\bin\lld-link.exe" ^
    -G Ninja 

cd tmp
ninja -j2

move ./main.exe ..
cd ..