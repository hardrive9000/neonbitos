#!/bin/bash
# Build ToyBox for NeonBitOS

set -e

# Load versions
source versions.txt

WORK_DIR="$(pwd)/build"
TOYBOX_SRC="$WORK_DIR/toybox"

if [ ! -d "$TOYBOX_SRC" ]; then
    echo "Error: ToyBox source not found. Run ./scripts/download-sources.sh first"
    exit 1
fi

cd "$TOYBOX_SRC"

echo "=== Building ToyBox for NeonBitOS ==="

# Create default configuration
if [ ! -f .config ]; then
    echo "Creating default ToyBox configuration..."
    make defconfig
fi

echo ""
echo "IMPORTANT: Manual configuration required!"
echo "=========================================="
echo "Please enable the following options in menuconfig:"
echo ""
echo "Navigate to: Pending (unfinished) commands"
echo "Enable these commands:"
echo "  [*] init"
echo "  [*] getty"
echo "  [*] vi"
echo ""
echo "See config/toybox-config-notes.txt for more details"
echo ""
read -p "Press Enter to open menuconfig..."

make menuconfig

echo "Compiling ToyBox..."
make -j$(nproc)

echo "ToyBox compiled successfully"
