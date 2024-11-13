@echo off
mkdir build
cd build
rem we use cmake!!
cmake ..
cmake --build .
rem mmm... copy..
xcopy /Y /E /I "..\res" "Debug"
cd Debug
alter-engine.exe
cd ..
cd ..