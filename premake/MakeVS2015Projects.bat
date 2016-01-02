SET libPath=..\..\Build\libs

premake5.exe vs2015

cd /D libs
for /r %%p in (*.lib,*.pdb) do echo d|xcopy "%%p" "%libPath%"
cd /D ..