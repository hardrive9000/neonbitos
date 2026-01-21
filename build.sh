#!/bin/bash
# Master build script for NeonBitOS
# This script orchestrates the entire build process

set -e

echo "╔═══════════════════════════════════════╗"
echo "║        NeonBitOS Build System         ║"
echo "║     Minimal Linux from Scratch        ║"
echo "╚═══════════════════════════════════════╝"
echo ""

# Make all scripts executable
chmod +x scripts/*.sh

echo "Installing dependencies. Running install-deps.sh..."
./scripts/install-deps.sh

# Download sources
echo ""
./scripts/download-sources.sh

# Build kernel
echo ""
./scripts/build-kernel.sh

# Build ToyBox
echo ""
./scripts/build-toybox.sh

# Build custom applications
echo ""
./scripts/build-custom-apps.sh

# Create root filesystem
echo ""
./scripts/create-rootfs.sh

# Create ISO
echo ""
./scripts/create-iso.sh

echo ""
echo "╔═══════════════════════════════════════╗"
echo "║     Build completed successfully!     ║"
echo "╚═══════════════════════════════════════╝"
echo ""
echo "Output files:"
echo "  - Kernel: build/linux/arch/x86/boot/bzImage"
echo "  - Initramfs: output/initramfs.cpio"
echo "  - ISO: output/neonbitos.iso"
echo "  - Root filesystem: build/rootfs/"
echo ""
echo "To run in QEMU:"
echo "  ./scripts/run-qemu.sh"
echo ""
echo "To write ISO to USB:"
echo "  sudo dd if=output/neonbitos.iso of=/dev/sdX bs=4M status=progress && sync"
