#!/bin/sh

# 1. Configuration
CC="gcc"
SRC="./src/hello.c"
OUT="hello.exe"
INC="-I./lib/include"
LIB_PATH="-L./lib/bin"
LIBS="-lraylib -lopengl32 -lgdi32 -lwinmm -luser32 -lshell32"

# 2. Build Process
echo "Compiling $SRC..."

$CC $SRC -o $OUT $INC $LIB_PATH $LIBS

# 3. Check if build succeeded
if [ $? -eq 0 ]; then
    echo "---------------------------"
    echo "Build Successful: $OUT"
    echo "Running game..."
    echo "---------------------------"
    ./$OUT
else
    echo "Build Failed!"
    exit 1
fi