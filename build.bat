@echo off
setlocal enabledelayedexpansion

REM Get the directory where this script is located
cd /d "%~dp0"

REM Find Visual Studio 2026 Community Edition (version 18.x)
set "VSINSTALL="
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -version "[18,19)" -property installationPath 2^>nul`) do (
    set "VSINSTALL=%%i"
    goto :found_vs
)

REM Fallback to hardcoded path if vswhere fails
if not defined VSINSTALL (
    if exist "C:\Program Files\Microsoft Visual Studio\18\Community" (
        set "VSINSTALL=C:\Program Files\Microsoft Visual Studio\18\Community"
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2026\Community" (
        set "VSINSTALL=C:\Program Files\Microsoft Visual Studio\2026\Community"
    )
)

:found_vs
if not exist "%VSINSTALL%" (
    echo Error: Visual Studio 2026 Community not found at "%VSINSTALL%"
    exit /b 1
)

REM Set up Visual C++ environment
call "%VSINSTALL%\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1

REM Build the project using MSBuild
echo Building FlightReservation-CLI...
msbuild FlightReservation-CLI.vcxproj ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:DesktopBuildProject=true ^
    /v:minimal

if !errorlevel! equ 0 (
    echo.
    echo Build completed successfully!
    exit /b 0
) else (
    echo.
    echo Build failed with error code !errorlevel!
    exit /b !errorlevel!
)

endlocal