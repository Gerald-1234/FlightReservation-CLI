@echo off
setlocal enabledelayedexpansion

REM Get the directory where this script is located (build folder)
set "BUILD_DIR=%~dp0"
set "PROJECT_DIR=%BUILD_DIR%.."
set "OUTPUT_DIR=%PROJECT_DIR%\x64\Debug"
set "OUTPUT_EXE=%OUTPUT_DIR%\FlightReservation-CLI.exe"
set "TARGET_EXE=%BUILD_DIR%FlightReservation-CLI.exe"
set "X64_DIR=%PROJECT_DIR%\x64"

cd /d "%PROJECT_DIR%"

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
if not defined VSINSTALL (
	echo Error: Visual Studio 2026 Community not found
	exit /b 1
)

if not exist "%VSINSTALL%" (
	echo Error: Visual Studio installation path does not exist: "%VSINSTALL%"
	exit /b 1
)

REM Set up Visual C++ environment
echo Setting up Visual Studio environment...
call "%VSINSTALL%\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
if !errorlevel! neq 0 (
	echo Error: Failed to set up Visual Studio environment
	exit /b 1
)

REM Build the project using MSBuild
msbuild "FlightReservation-CLI.vcxproj" ^
	/p:Configuration=Debug ^
	/p:Platform=x64 ^
	/v:minimal

if !errorlevel! neq 0 (
	echo.
	echo Build failed with error code !errorlevel!
	exit /b !errorlevel!
)

REM Check if build output exists
if not exist "%OUTPUT_EXE%" (
	echo Error: Build output not found at "%OUTPUT_EXE%"
	exit /b 1
)

echo Copying build artifacts...

REM Remove old files in build folder
if exist "%TARGET_EXE%" (
	del /f /q "%TARGET_EXE%" 2>nul
)
del /f /q "%BUILD_DIR%*.dll" 2>nul

REM Copy executable to build folder with retry logic
set "RETRY_COUNT=0"
set "MAX_RETRIES=3"

:copy_exe_retry
if !RETRY_COUNT! gtr !MAX_RETRIES! (
	echo Error: Failed to copy executable after !MAX_RETRIES! retries
	exit /b 1
)

copy "%OUTPUT_EXE%" "%TARGET_EXE%" >nul 2>&1
if !errorlevel! equ 0 (
	echo - Executable copied successfully
	goto :copy_dlls
)

set /a RETRY_COUNT+=1
if !RETRY_COUNT! leq !MAX_RETRIES! (
	timeout /t 1 /nobreak >nul
	goto :copy_exe_retry
)

:copy_dlls
REM Copy all DLL files from output directory to build folder
set "DLL_COPY_FAILED=0"
set "DLL_COUNT=0"

for %%F in ("%OUTPUT_DIR%\*.dll") do (
	set /a DLL_COUNT+=1
	set "DLL_NAME=%%~nxF"

	copy "%%F" "%BUILD_DIR%%%~nxF" >nul 2>&1
	if !errorlevel! equ 0 (
		echo - DLL copied: !DLL_NAME!
	) else (
		echo - Error: Failed to copy DLL: !DLL_NAME!
		set "DLL_COPY_FAILED=1"
	)
)

if !DLL_COUNT! equ 0 (
	echo - No DLL files found in output directory
)

REM Only clean up x64 folder if ALL DLLs were copied successfully
if !DLL_COPY_FAILED! equ 1 (
	echo.
	echo Warning: Some DLL files failed to copy. Skipping x64 folder cleanup.
	echo Build completed with warnings.
	echo Executable path: %TARGET_EXE%
	exit /b 0
)

REM Clean up x64 folder after successful copy
echo Cleaning up build artifacts...
set "CLEANUP_RETRY=0"
set "MAX_CLEANUP_RETRIES=10"

:cleanup_retry
if !CLEANUP_RETRY! gtr !MAX_CLEANUP_RETRIES! (
	echo Warning: Failed to delete x64 folder after !MAX_CLEANUP_RETRIES! retries
	goto :build_success
)

if exist "%X64_DIR%" (
	REM Remove read-only flags recursively
	attrib -r "%X64_DIR%\*" /s /d 2>nul

	REM Delete all files in Debug folder if it exists
	if exist "%X64_DIR%\Debug" (
		del /s /f /q "%X64_DIR%\Debug\*.*" 2>nul
	)

	REM Delete all files in root x64 folder
	del /s /f /q "%X64_DIR%\*.*" 2>nul

	REM Delete all subdirectories
	for /d %%D in ("%X64_DIR%\*") do (
		rmdir /s /q "%%D" 2>nul
	)

	REM Try final removal of x64 directory
	rmdir /q "%X64_DIR%" 2>nul
	if !errorlevel! equ 0 (
		echo - x64 folder deleted successfully
		goto :build_success
	)

	set /a CLEANUP_RETRY+=1
	timeout /t 2 /nobreak >nul
	goto :cleanup_retry
)

:build_success
echo.
echo Build completed successfully.
echo Executable path: %TARGET_EXE%
exit /b 0

endlocal

	set /a CLEANUP_RETRY+=1
	timeout /t 2 /nobreak >nul
	goto :cleanup_retry
)

:build_success
echo.
echo Build completed successfully.
echo Executable path: %TARGET_EXE%
exit /b 0

endlocal