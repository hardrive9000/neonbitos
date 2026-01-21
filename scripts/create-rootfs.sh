#!/bin/bash
# Create root filesystem for NeonBitOS

set -e

WORK_DIR="$(pwd)/build"
TOYBOX_SRC="$WORK_DIR/toybox"
ROOTFS_DIR="$WORK_DIR/rootfs"
OUTPUT_DIR="$(pwd)/output"
CUSTOM_APPS_BUILD="$WORK_DIR/custom-apps-build"

if [ ! -f "$TOYBOX_SRC/toybox" ]; then
    echo "Error: ToyBox not built. Run ./scripts/build-toybox.sh first"
    exit 1
fi

echo "=== Creating NeonBitOS root filesystem ==="

# Clean and create rootfs directory
rm -rf "$ROOTFS_DIR"
mkdir -p "$ROOTFS_DIR"

# Install ToyBox to rootfs
echo "Installing ToyBox..."
cd "$TOYBOX_SRC"
PREFIX="$ROOTFS_DIR" make install

cd "$ROOTFS_DIR"

# Create init symlink
echo "Creating init symlink..."
ln -s sbin/init init

# Create necessary directories
echo "Creating directory structure..."
mkdir -p lib/x86_64-linux-gnu lib64 dev sys proc usr/share etc/init.d

# Copy required shared libraries
echo "Copying shared libraries..."

# Libraries for ToyBox/init
cp -L /lib/x86_64-linux-gnu/libcrypt.so.1 lib/x86_64-linux-gnu/
cp -L /lib/x86_64-linux-gnu/libm.so.6 lib/x86_64-linux-gnu/
cp -L /lib/x86_64-linux-gnu/libc.so.6 lib/x86_64-linux-gnu/
cp -L /lib64/ld-linux-x86-64.so.2 lib64/

# Copy bash and its dependencies
echo "Installing bash as /bin/sh..."
cp /bin/bash bin/sh
cp -L /lib/x86_64-linux-gnu/libtinfo.so.6 lib/x86_64-linux-gnu/

# Copy configuration files from repository
echo "Installing configuration files..."
cp "$(dirname "$WORK_DIR")/rootfs/etc/init.d/rcS" etc/init.d/
chmod +x etc/init.d/rcS
echo "rcS installed"

# Copy inittab
cp "$(dirname "$WORK_DIR")/rootfs/etc/inittab" etc/
echo "inittab installed"

# Copy profile
cp "$(dirname "$WORK_DIR")/rootfs/etc/profile" etc/
echo "profile installed"

# Install custom applications
if [ -d "$CUSTOM_APPS_BUILD" ]; then
    echo "Installing custom applications..."
    if [ -f "$CUSTOM_APPS_BUILD/pidigits" ]; then
        cp "$CUSTOM_APPS_BUILD/pidigits" bin/
        echo "pidigits installed"
    fi
    if [ -f "$CUSTOM_APPS_BUILD/termrex" ]; then
        cp "$CUSTOM_APPS_BUILD/termrex" bin/
        echo "termrex installed"
    fi
fi

# Create initramfs
echo "Creating initramfs..."
mkdir -p "$OUTPUT_DIR"
find . | cpio -o -H newc > "$OUTPUT_DIR/initramfs.cpio"

echo "Root filesystem created: $OUTPUT_DIR/initramfs.cpio"
echo "Full filesystem available at: $ROOTFS_DIR"
