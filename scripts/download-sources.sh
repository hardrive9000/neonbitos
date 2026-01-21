#!/bin/bash
# Download kernel and ToyBox sources for NeonBitOS

set -e

# Load versions
source versions.txt

WORK_DIR="$(pwd)/build"
mkdir -p "$WORK_DIR"
cd "$WORK_DIR"

echo "=== Downloading NeonBitOS sources ==="

# Download Linux kernel
if [ ! -d "linux" ]; then
    echo "Downloading Linux kernel ${KERNEL_VERSION}..."
    wget -q --show-progress "$KERNEL_URL"
    tar xf "linux-${KERNEL_VERSION}.tar.xz"
    rm "linux-${KERNEL_VERSION}.tar.xz"
    mv "$KERNEL_DIR" linux
    echo "Kernel downloaded"
else
    echo "Kernel already downloaded"
fi

# Clone ToyBox
if [ ! -d "toybox" ]; then
    echo "Cloning ToyBox..."
    git clone --depth 1 -b "$TOYBOX_BRANCH" "$TOYBOX_REPO" toybox
    echo "ToyBox cloned"
else
    echo "ToyBox already cloned"
fi

# Clone Termrex
if [ ! -d "termrex" ]; then
    echo "Cloning Termrex (endless runner game)..."
    git clone --depth 1 -b "$TERMREX_BRANCH" "$TERMREX_REPO" termrex
    echo "Termrex cloned"
else
    echo "Termrex already cloned"
fi

echo "All sources ready in $WORK_DIR"
