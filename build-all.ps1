function Throw-OnError {
    if ($LASTEXITCODE -ne 0) {
        Write-Error "The last command exited with error code $LASTEXITCODE."
        throw $LASTEXITCODE
    }
}

Write-Host "Building everything ..."

Push-Location "engine"
    ./build.ps1
Pop-Location
Throw-OnError

Push-Location "testbed"
    ./build.ps1
Pop-Location
Throw-OnError

Write-Information "Done builing all assemblies."
