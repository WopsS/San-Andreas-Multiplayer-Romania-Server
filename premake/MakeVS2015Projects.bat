SET libPath=..\..\Build\libs

premake5.exe vs2015

cd /D libs
for /r %%p in (*.lib) do echo d|xcopy "%%p" "%libPath%"
cd /D ..