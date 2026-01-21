#!/bin/bash
# Install build dependencies for NeonBitOS

set -e

echo "=== Installing NeonBitOS build dependencies ==="

sudo apt update && \
sudo apt install -y \
    bzip2 \
    git \
    make \
    gcc \
    g++ \
    libncurses-dev \
    flex \
    bison \
    bc \
    cpio \
    libelf-dev \
    libssl-dev \
    qemu-system-x86 \
    genisoimage \
    syslinux \
    isolinux

echo "All dependencies installed successfully"
