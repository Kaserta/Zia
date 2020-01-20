#!/bin/sh

conan remote add conan-centers https://conan.bintray.com
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default

#compile
mkdir -p build
cd build
conan install .. --build=missing
cmake .. -G "Unix Makefiles"
cmake --build .
make test
cd ..
gcov  $(find build/test/CMakeFiles/Glados.dir -iname "*.cpp.o")
gcovr -g -e test