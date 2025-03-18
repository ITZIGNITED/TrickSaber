Param(
    [Parameter(Mandatory=$false)]
    [Switch]$clean,
    [Parameter(Mandatory=$false)]
    [Switch]$release
)

$buildType = "Debug"
if ($release.IsPresent) {
    $buildType = "RelWithDebInfo"
    echo "Building release"
} else {
    echo "Building debug"
}

$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

# if user specified clean, remove all build files
if (($clean.IsPresent) -or (-not (Test-Path -Path "build")))
{
    $out = new-item -Path build -ItemType Directory
}

& cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$buildType" . -B build
& cmake --build ./build
$ExitCode = $LastExitCode
exit $ExitCode
