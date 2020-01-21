
conan remote add conan-centers https://conan.bintray.com
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default

mkdir build
cd build
conan install .. --build=missing
cmake .. -G "Visual Studio 16 2019"
cmake --build .