@ECHO OFF
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\vcvars32.bat"
ECHO Including CL....
ECHO Compiling.......
cl /Fetemp.exe /EHsc AppRecommendation/*.cpp

if %ERRORLEVEL% GEQ 1 (
	ECHO ----- Program failed to compile ------
) else (
	ECHO +++++ Program sucessfully compiled ++++
)