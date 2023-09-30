$srcFiles=""
# Write a for loop to iterate over all files that have the extension ".cpp"
foreach ($file in Get-ChildItem -Path "./" -Filter *.cpp -Recurse) {
    # Append the file path to the $srcFiles variable
    $srcFiles += $file.FullName + " "
}

$assembly="testbed"
$compilerFlags="-g"
$includeFlags="-Isrc -I../engine/src/"
$linkerFlags="-lengine -L../bin/ "
$defines="-D_DEBUG -DCIMPORT"

Write-Host "Building $assembly ..."

"clang++ $srcFiles $compilerFlags -o ../bin/$assembly.exe $defines $includeFlags $linkerFlags" | Invoke-Expression
