@echo off
rmdir /s /q "bin/Release"
rmdir /s /q "build"
rmdir /s /q "linklib"
mkdir build
mkdir linklib
cd build
"../cmake/bin/cmake.exe" -G "Visual Studio 10" ..
