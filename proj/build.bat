@echo off
mkdir ..\build
pushd ..\build
cl -Zi -EHsc ..\proj\src\main.cpp user32.lib Gdi32.lib
%1
popd

