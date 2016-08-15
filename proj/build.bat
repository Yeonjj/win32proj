@echo off
mkdir ..\build
pushd ..\build

cl -Zi -EHsc ..\proj\src\main.cpp user32.lib Gdi32.lib

IF "%1"=="1" echo toolon && goto toolon 
IF "%1"=="2" echo startapp && goto startapp
IF "%1"=="" echo default && goto default


:toolon
devenv %2.exe
%2

:startapp
main

:default

popd

