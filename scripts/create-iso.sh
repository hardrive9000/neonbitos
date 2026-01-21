#!/bin/bash
# Create bootable ISO for NeonBitOS using kernel's make isoimage

set -e

WORK_DIR="$(pwd)/build"
KERNEL_SRC="$WORK_DIR/linux"
OUTPUT_DIR="$(pwd)/output"
INITRD="$OUTPUT_DIR/initramfs.cpio"

if [ ! -f "$KERNEL_SRC/arch/x86/boot/bzImage" ]; then
    echo "Error: Kernel not built. Run ./scripts/build-kernel.sh first"
    exit 1
fi

if [ ! -f "$INITRD" ]; then
    echo "Error: Initramfs not found. Run ./scripts/create-rootfs.sh first"
    exit 1
fi

echo "=== Creating NeonBitOS ISO (Legacy BIOS only) ==="

cd "$KERNEL_SRC"

echo "→ Building ISO with kernel's make isoimage..."
make isoimage FDARGS="initrd=$INITRD" FDINITRD="$INITRD"

# Copy ISO to output directory
mkdir -p "$OUTPUT_DIR"
cp arch/x86/boot/image.iso "$OUTPUT_DIR/neonbitos.iso"

echo ""
echo "ISO created: $OUTPUT_DIR/neonbitos.iso"
echo ""
echo "Boot modes supported:"
echo "BIOS Legacy (ISOLINUX)"
echo "UEFI (not supported with this method)"
echo ""
echo "To write to USB:"
echo "  sudo dd if=$OUTPUT_DIR/neonbitos.iso of=/dev/sdX bs=4M status=progress && sync"
echo ""
echo "To test in QEMU:"
echo "  qemu-system-x86_64 -cdrom $OUTPUT_DIR/neonbitos.iso"
