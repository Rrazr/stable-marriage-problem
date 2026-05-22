# build_and_run.ps1

# 1. Find Visual Studio using vswhere.exe
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (!(Test-Path $vswhere)) {
    Write-Error "vswhere.exe not found. Visual Studio might not be installed."
    exit 1
}

# Use -products * to ensure Build Tools are found
$vsPath = & $vswhere -latest -products * -property installationPath
if (-not $vsPath) {
    Write-Error "Could not find Visual Studio installation path."
    exit 1
}

# 2. Find and Run VsDevCmd.bat to inject environment variables into the current session
$devCmd = "$vsPath\Common7\Tools\VsDevCmd.bat"
if (Test-Path $devCmd) {
    Write-Host "Initializing Visual Studio Environment..." -ForegroundColor Cyan
    # Run the batch file and 'set' in a single cmd instance, then parse the output
    $envVars = cmd /c "`"$devCmd`" -arch=x64 -host_arch=x64 && set"
    foreach ($line in $envVars) {
        if ($line -match "^(.*?)=(.*)$") {
            $name = $matches[1]
            $value = $matches[2]
            if ($name -ne "PATH") {
                Set-Item "env:$name" $value
            } else {
                # Prepend to PATH to ensure we use the VS tools
                $env:PATH = "$value;$env:PATH"
            }
        }
    }
}

# 3. Run CMake
Write-Host "`nConfiguring project..." -ForegroundColor Green
cmake -B build
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "`nBuilding project..." -ForegroundColor Green
cmake --build build
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

# 4. Clear screen and run the App
Clear-Host
if (Test-Path "build\Debug\StableMarriageApp.exe") {
    & "build\Debug\StableMarriageApp.exe"
} elseif (Test-Path "build\StableMarriageApp.exe") {
    & "build\StableMarriageApp.exe"
} else {
    Write-Error "Could not find StableMarriageApp.exe"
}
