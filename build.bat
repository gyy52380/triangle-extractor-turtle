@echo off
setlocal

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

cd /d %~dp0


set FILES=unity.cpp

set CL_OUTPUT=-Fo"run_tree/objects/" -Fe"run_tree/output.exe"
set CL_LIB_INCLUDE=-I"include-dir"
set CL_FLAGS=-Z7 -Oi -MT -EHsc -GR- -MP -fp:fast -fp:except- -nologo -std:c++17
set CL_UNITY_BUILD_FLAGS=-Gm-
set CL_INPUT=%CL_OUTPUT% %CL_LIB_INCLUDE% %CL_FLAGS% %CL_UNITY_BUILD_FLAGS%


set LIBRARIES=opengl32.lib glu32.lib lib/glew32.lib lib/SDL2.lib

set LINK_FLAGS=-nologo -debug:fastlink -opt:ref -subsystem:console
set LINK_UNITY_FLAGS=-incremental:no

set LINK_INPUT=%LINK_FLAGS% %LINK_UNITY_FLAGS%


cl %CL_INPUT% %FILES% -link %LINK_INPUT% %LIBRARIES%

pause