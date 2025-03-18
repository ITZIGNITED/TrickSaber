param (
    [Parameter(Mandatory=$false)]
    [Switch] $clean,
    [Parameter(Mandatory=$false)]
    [Switch] $useDebug,
    [Parameter(Mandatory=$false)]
    [Switch]$release,
    [Parameter(Mandatory=$false)]
    [Switch]$log,
    [Parameter(Mandatory=$false)]
    [Switch] $self,
    [Parameter(Mandatory=$false)]
    [Switch] $file,
    [Parameter(Mandatory=$false)]
    [Switch] $all
)

& $PSScriptRoot/build.ps1 -clean:$clean -release:$release
if (-not ($LastExitCode -eq 0)) {
    echo "build failed, not copying"
    exit
}

if ($useDebug -eq $true) {
    & adb push build/debug/libtrick-saber.so /sdcard/ModData/com.beatgames.beatsaber/Modloader/mods/libtrick-saber.so
} else {
    & adb push build/libtrick-saber.so /sdcard/ModData/com.beatgames.beatsaber/Modloader/mods/libtrick-saber.so
}

& $PSScriptRoot/restart-game.ps1

if ($log -eq $true) { & $PSScriptRoot/start-logging.ps1 -self:$self -all:$all -custom:$custom -file:$file }
