#!/bin/bash
# Build Linux kernel for NeonBitOS

set -e

# Load versions
source versions.txt

WORK_DIR="$(pwd)/build"
KERNEL_SRC="$WORK_DIR/linux"

if [ ! -d "$KERNEL_SRC" ]; then
    echo "Error: Kernel source not found. Run ./scripts/download-sources.sh first"
    exit 1
fi

cd "$KERNEL_SRC"

echo "=== Building NeonBitOS kernel ==="

# Create default configuration
if [ ! -f .config ]; then
    echo "Creating default kernel configuration..."
    make defconfig
fi

echo ""
echo "IMPORTANT: Manual configuration required!"
echo "=========================================="
echo "Please enable the following options in menuconfig:"
echo ""
echo "1. Device Drivers -> Graphics support ->"
echo "   Direct Rendering Manager (XFree86 4.1.0 and higher DRI support)"
echo "   [*] Enable legacy fbdev support for your modesetting driver"
echo ""
echo "2. Device Drivers -> Graphics support ->"
echo "   Direct Rendering Manager (XFree86 4.1.0 and higher DRI support) ->"
echo "   [*] DRM Support for bochs dispi vga interface (qemu stdvga)"
echo ""
echo "3. Device Drivers -> Graphics support ->"
echo "   [*] Bootup logo"
echo ""
echo "See config/kernel-config-notes.txt for more details"
echo ""
read -p "Press Enter to open menuconfig..."

make menuconfig

echo "Compiling kernel (this may take several minutes)..."

# Set custom build info for NeonBitOS branding
export KBUILD_BUILD_USER="$KBUILD_BUILD_USER"
export KBUILD_BUILD_HOST="$KBUILD_BUILD_HOST"

make -j$(nproc)

echo "Kernel compiled successfully: $KERNEL_SRC/arch/x86/boot/bzImage"
