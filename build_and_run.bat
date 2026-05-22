@echo off
setlocal

echo Configuring the project with CMake...
cmake -B build
if %errorlevel% neq 0 (
    echo [ERROR] CMake configuration failed.
    pause
    exit /b %errorlevel%
)

echo Compiling...
cmake --build build
if %errorlevel% neq 0 (
    echo [ERROR] Build failed.
    pause
    exit /b %errorlevel%
)

echo.
echo Running Stable Marriage Solver...
echo -----------------------------------

:: Windows CMake generators (like Visual Studio) often put the exe in a Debug folder
if exist "build\Debug\StableMarriageApp.exe" (
    .\build\Debug\StableMarriageApp.exe
)
else if exist "build\StableMarriageApp.exe" (
    .\build\StableMarriageApp.exe
) 
else (
    echo [ERROR] Could not find executable.
)

pause
endlocal
