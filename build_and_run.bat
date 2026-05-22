@echo off
setlocal

:: Attempt to automatically initialize the Visual Studio Developer environment
:: This allows CMake and the MSVC compiler (cl.exe) to be found in a normal Command Prompt
:: Added -products * because Build Tools installations are sometimes hidden by default
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -property installationPath`) do set "VS_PATH=%%i"
)

if defined VS_PATH (
    if exist "%VS_PATH%\Common7\Tools\VsDevCmd.bat" (
        echo Initializing Visual Studio Environment...
        call "%VS_PATH%\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64 >nul
    )
) else (
    echo [WARNING] Visual Studio not found automatically. 
    echo If CMake fails, please run this from a Developer Command Prompt.
)

echo.
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

:: Clear the screen before running the app
cls

:: Windows CMake often puts the executable inside a Debug/Release folder
if exist "build\Debug\StableMarriageApp.exe" (
    .\build\Debug\StableMarriageApp.exe
) else if exist "build\StableMarriageApp.exe" (
    .\build\StableMarriageApp.exe
) else (
    echo [ERROR] Could not find executable.
    pause
)

endlocal
