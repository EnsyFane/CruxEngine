#!/bin/bash
set echo on
mkdir -p ../bin

srcFiles=$(find . -type f -name "*.cpp")

assembly="testbed"
compilerFlags="-g -fdeclspec -fPIC" 
includeFlags="-Isrc -I../engine/src/"
linkerFlags="-L../bin/ -lengine -Wl,-rpath,."
defines="-D_DEBUG -DCIMPORT"

echo "Building $assembly..."

clang $srcFiles $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
