cd ..
pwd
mkdir -p "build"
cd build
cmake ..
cmake --build .
./sorting_tests

sleep 20