#!/bin/bash
set echo on
mkdir -p ../bin

srcFiles=$(find . -type f -name "*.cpp")

assembly="engine"
compilerFlags="-g -shared -fdeclspec -fPIC"
includeFlags="-Isrc -I$VULKAN_SDK/include"
linkerFlags="-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L$VULKAN_SDK/lib -L/usr/X11R6/lib"
defines="-D_DEBUG -DKEXPORT"

echo "Building $assembly..."

clang $srcFiles $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags
