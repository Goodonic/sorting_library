pwd
cd ..
mkdir -p build
cd build
cmake .. -DBUILD_TESTS=ON
cmake --build . --config Debug