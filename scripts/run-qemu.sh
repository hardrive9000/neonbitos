#!/bin/bash
# Run NeonBitOS in QEMU

set -e

WORK_DIR="$(pwd)/build"
KERNEL="$WORK_DIR/linux/arch/x86/boot/bzImage"
INITRD="$(pwd)/output/initramfs.cpio"

if [ ! -f "$KERNEL" ]; then
    echo "Error: Kernel not found. Run ./scripts/build-kernel.sh first"
    exit 1
fi

if [ ! -f "$INITRD" ]; then
    echo "Error: Initramfs not found. Run ./scripts/create-rootfs.sh first"
    exit 1
fi

echo "=== Launching NeonBitOS in QEMU ==="
echo "Kernel: $KERNEL"
echo "Initrd: $INITRD"
echo ""
echo "Press Ctrl+A then X to exit QEMU"
echo ""

qemu-system-x86_64 \
    -kernel "$KERNEL" \
    -initrd "$INITRD"
