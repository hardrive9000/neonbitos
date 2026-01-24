#!/bin/bash
# Build nano editor for NeonBitOS
# Static binary for easy text editing

set -e

# Load versions
source versions.txt

WORK_DIR="$(pwd)/build"
NANO_SRC="$WORK_DIR/nano"

if [ -d "$NANO_SRC" ]; then
    echo "=== Building nano text editor for NeonBitOS ==="
    cd "$NANO_SRC"

    # Clean any previous build artifacts (if Makefile exists)
    echo "Cleaning previous builds..."
    if [ -f Makefile ]; then
        make clean > /dev/null 2>&1 || true
        make distclean > /dev/null 2>&1 || true
    else
        echo "(No previous build found, skipping clean)"
    fi

    # Configure for static build
    echo "Configuring nano (static build, English only)..."

    # Force English locale during build
    export LANG="$LANG"
    export LC_ALL="$LC_ALL"

    # Note: We disable some features to reduce size:
    # --disable-nls: No translations (smaller, English only)
    # --disable-browser: No file browser (can still open files)
    # --disable-help: No built-in help (saves ~50KB)
    # Keep: syntax highlighting, search, etc.
    ./configure --enable-utf8 --disable-nls --disable-browser --disable-help LDFLAGS="-static" CFLAGS="-Os"

    # Compile with English locale
    echo "Compiling nano (skipping documentation)..."
    LANG="$LANG" LC_ALL="$LC_ALL" make -j$(nproc)

    # Strip to reduce size
    echo "Stripping binary..."
    strip src/nano
    echo "Size: $(du -h src/nano | cut -f1)"
    echo "nano compiled successfully"
else
    echo "nano source not found, skipping"
fi
