#!/bin/bash

conan remote add conan-centers https://conan.bintray.com
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default