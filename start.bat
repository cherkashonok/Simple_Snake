if not exist "tmp" (
    mkdir tmp
)

cmake ^
    -S . ^
    -B tmp ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -G Ninja 

cd tmp
ninja -j2

move ./main.exe ..
cd ..