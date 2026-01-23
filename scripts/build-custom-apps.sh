#!/bin/bash
# Build custom applications for NeonBitOS

set -e

# Load versions
source versions.txt

WORK_DIR="$(pwd)/build"
TERMREX_SRC="$WORK_DIR/termrex"
CUSTOM_APPS_DIR="$(pwd)/custom-apps"
BUILD_DIR="$WORK_DIR/custom-apps-build"

echo "=== Building custom applications for NeonBitOS ==="

mkdir -p "$BUILD_DIR"

# Build pidigits
echo "Compiling pidigits (BBP Pi calculator)..."
cd "$CUSTOM_APPS_DIR/pidigits"
make clean
make
cp pidigits "$BUILD_DIR/"
echo "pidigits compiled"

# Build ahorcado
echo "Compiling ahorcado..."
cd "$CUSTOM_APPS_DIR/ahorcado"
make clean
make
cp ahorcado "$BUILD_DIR/"
echo "ahorcado compiled"

# Build termrex
if [ -d "$TERMREX_SRC" ]; then
    echo "Compiling termrex (endless runner game)..."
    cd "$TERMREX_SRC"
    make clean || true
    make CXX=g++ CXXFLAGS="-std=c++17 -Wall -Wextra -static-libstdc++ -static-libgcc -O2" release
    cp build/termrex "$BUILD_DIR/"
    echo "termrex compiled"
else
    echo "termrex source not found, skipping"
fi

echo "All custom applications compiled in $BUILD_DIR"
