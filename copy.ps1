param (
    [Parameter(Mandatory=$false)]
    [Switch] $clean,
    [Parameter(Mandatory=$false)]
    [Switch] $useDebug,
    [Parameter(Mandatory=$false)]
    [Switch]$release,
    [Parameter(Mandatory=$false)]
    [Switch]$log
)

& $PSScriptRoot/build.ps1 -clean:$clean -release:$release
if (-not ($LastExitCode -eq 0)) {
    echo "build failed, not copying"
    exit
}

if ($useDebug -eq $true) {
    $fileName = Get-ChildItem lib*.so -Path "build/debug" -Name
} else {
    $fileName = Get-ChildItem lib*.so -Path "build/" -Name
}

& adb push build/$fileName /sdcard/ModData/com.beatgames.beatsaber/Modloader/mods/$fileName

& adb shell am force-stop com.beatgames.beatsaber
& adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
Start-Sleep -Seconds 1.0
& adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
if ($log.IsPresent) {
    & ./log.ps1
}
