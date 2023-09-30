$srcFiles=""
# Write a for loop to iterate over all files that have the extension ".cpp"
foreach ($file in Get-ChildItem -Path "./" -Filter *.cpp -Recurse) {
    # Append the file path to the $srcFiles variable
    $srcFiles += $file.FullName + " "
}

$assembly="engine"
$compilerFlags="-g -shared -Wvarargs -Wall -Werror"
$includeFlags="-Isrc -I$env:VULKAN_SDK/Include"
$linkerFlags="-luser32 -lvulkan-1 -L$env:VULKAN_SDK/Lib"
$defines="-D_DEBUG -DCEXPORT -D_CRT_SECURE_NO_WARNINGS"

Write-Host "Building $assembly ..."

"clang++ $srcFiles $compilerFlags -o ../bin/$assembly.dll $defines $includeFlags $linkerFlags" | Invoke-Expression
