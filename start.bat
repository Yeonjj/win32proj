@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
set path=C:\work\win32proj;%path%
subst W: C:\work
W: