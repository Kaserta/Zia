#!/bin/sh

#setup conan
#conan remote update bincrafters https://api.bintray.com/conan/bincrafters/public-conan
#conan profile update settings.compiler.libcxx=libstdc++11 default

#deleting files
./clean.sh

#compile
mkdir -p build
cd build
conan install .. --build=missing
cmake .. -G "Unix Makefiles"
cmake --build .
