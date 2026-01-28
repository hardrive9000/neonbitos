#!/bin/bash
# Build strace for NeonBitOS
# Static binary for system call tracing

set -e

# Load versions
source versions.txt

WORK_DIR="$(pwd)/build"
STRACE_SRC="$WORK_DIR/strace"

if [ -d "$STRACE_SRC" ]; then
    echo "=== Building strace for NeonBitOS ==="
    cd "$STRACE_SRC"

    # Clean any previous build artifacts (if Makefile exists)
    echo "Cleaning previous builds..."
    if [ -f Makefile ]; then
        make clean > /dev/null 2>&1 || true
        make distclean > /dev/null 2>&1 || true
    else
        echo "(No previous build found, skipping clean)"
    fi

    # Configure for static build
    echo "Configuring strace (static build)..."
    ./configure --enable-mpers=no LDFLAGS="-static -pthread" CFLAGS="-Os"

    # Compile
    echo "Compiling strace..."
    make -j$(nproc)

    # Strip to reduce size
    echo "Stripping binary..."
    strip src/strace
    echo "Size: $(du -h src/strace | cut -f1)"
    echo "strace compiled successfully"
else
    echo "strace source not found, skipping"
fi
