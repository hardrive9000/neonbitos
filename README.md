# NeonBitOS

```
      ╔═════════════╗
      ║  ╔═══╗ ╔═╗  ║
      ║  ║ █ ║ ║█║  ║
      ║  ╚═╦═╝ ╚═╝  ║
      ║    ║        ║
      ╚════╩════════╝
        ∿ ∿ ∿ ∿ ∿
     N E O N B I T O S
 Minimal Linux from Scratch
```

**A minimal, cyberpunk-inspired Linux distribution built from scratch**

NeonBitOS is an ultra-minimal Linux distribution featuring:
- 🔥 **Linux Kernel 6.12.65** with framebuffer graphics support
- 🛠️ **ToyBox** as userspace (init, shell, and core utilities)
- 🎮 **Termrex** - Endless runner game
- 💀 **ahorcado** - Spanish hangman word game (test your vocabulary!)
- 🔢 **pidigits** - Bailey-Borwein-Plouffe Pi calculator
- ⚡ **Minimal footprint** - Only essential components
- 🚀 **Fast boot** - Boots directly to a shell
- 💾 **Fully reproducible** - Built entirely from source

## 🎯 Project Philosophy

NeonBitOS demonstrates the bare minimum required for a bootable Linux system. It's perfect for:
- Learning how Linux distributions are built
- Understanding kernel configuration and initramfs
- Creating custom embedded systems
- Cyberpunk aesthetic appreciation

## 📋 Prerequisites

- Debian/Ubuntu-based Linux system (or adapt package names). I used Lubuntu 24.04.3.
- ~2GB free disk space
- ~10 minutes build time (depending on CPU)

## 🚀 Quick Start

### One-command build:
```bash
./build.sh
```

This will:
1. Install all required dependencies
2. Download Linux kernel, ToyBox, and Termrex sources
3. Configure and compile the kernel (with interactive menuconfig)
4. Configure and compile ToyBox (with interactive menuconfig)
5. Compile custom applications (pidigits, termrex)
6. Create the root filesystem and initramfs
7. Generate bootable ISO

### Run NeonBitOS:
```bash
# In QEMU
./scripts/run-qemu.sh

# Or boot the ISO
qemu-system-x86_64 -cdrom output/neonbitos.iso
```

## 🔧 Manual Build Process

If you prefer step-by-step control:

```bash
# 1. Install dependencies
./scripts/install-deps.sh

# 2. Download sources
./scripts/download-sources.sh

# 3. Build kernel
./scripts/build-kernel.sh

# 4. Build ToyBox
./scripts/build-toybox.sh

# 5. Build custom apps
./scripts/build-custom-apps.sh

# 6. Create filesystem
./scripts/create-rootfs.sh

# 7. Create ISO
./scripts/create-iso.sh

# 8. Run in QEMU
./scripts/run-qemu.sh
```

## 📁 Repository Structure

```
neonbitos/
├── build.sh                       # Master build script
├── versions.txt                   # Component versions
├── config/
│   ├── kernel-config-notes.txt    # Kernel configuration guide
│   └── toybox-config-notes.txt    # ToyBox configuration guide
├── rootfs/
│   └── etc/
│       ├── init.d/rcS             # Init script
│       ├── inittab                # Init configuration
│       └── profile                # Shell profile with neon logo
├── custom-apps/
│   ├── pidigits/                  # BBP Pi calculator (public domain)
│   │   ├── pidigits.c
│   │   ├── Makefile
│   │   └── README.md
│   └── ahorcado/                  # Simple hangman game (public domain)
│       ├── ahorcado.c
│       ├── Makefile
│       └── README.md
├── scripts/
│   ├── install-deps.sh            # Install build dependencies
│   ├── download-sources.sh        # Download kernel, ToyBox, termrex
│   ├── build-kernel.sh            # Compile kernel
│   ├── build-toybox.sh            # Compile ToyBox
│   ├── build-custom-apps.sh       # Compile pidigits, hangman and termrex
│   ├── create-rootfs.sh           # Build root filesystem
│   ├── create-iso.sh              # Create bootable ISO
│   └── run-qemu.sh                # Launch in QEMU
└── README.md
```

## ⚙️ Configuration Details

### Kernel Configuration
Base: `defconfig` with these additions:
- DRM support for QEMU graphics (bochs driver)
- Legacy fbdev emulation for modesetting
- Bootup logo

See `config/kernel-config-notes.txt` for details.

### ToyBox Configuration
Base: `defconfig` with pending commands:
- `init` - System initialization
- `getty` - Terminal login
- `vi` - Text editor

See `config/toybox-config-notes.txt` for details.

### Init Script (`/etc/init.d/rcS`)
Minimal initialization:
```bash
#!/bin/sh
mount -t devtmpfs devtmpfs /dev
mount -t sysfs /sys /sys
mount -t proc /proc /proc
dmesg -n 1
```

## 🎮 Applications

### pidigits - BBP Pi Calculator
Calculate hexadecimal digits of π using the Bailey-Borwein-Plouffe algorithm.

```bash
pidigits              # First 100 hex digits
pidigits 1000         # First 1000 hex digits
pidigits -n 1000000   # The millionth digit (instantly!)
```

**Special feature**: Can calculate the nth digit without computing previous digits!

### ahorcado - Simple Hangman Game in Spanish
The game selects a random word and displays the word's category as a clue. You must guess it letter by letter. You have 6 attempts before losing.

```bash
ahorcado
```

### termrex - Endless Runner Game
A fun terminal-based endless runner game. Jump over obstacles and see how far you can go!

```bash
termrex
```

## 💿 Creating Bootable Media

### Write ISO to USB:
```bash
sudo dd if=output/neonbitos.iso of=/dev/sdX bs=4M status=progress && sync
```

## 🔄 Customization

### Change kernel version:
Edit `versions.txt`:
```bash
KERNEL_VERSION=6.13.0  # or any other version
```

### Modify init script:
Edit `rootfs/etc/init.d/rcS` and rebuild:
```bash
./scripts/create-rootfs.sh
./scripts/create-iso.sh
```

### Customize welcome banner:
Edit `rootfs/etc/profile` to change the ASCII art logo or colors.

### Add more applications:
1. Add source code to `custom-apps/`
2. Update `scripts/build-custom-apps.sh`
3. Rebuild

## 🐛 Troubleshooting

**Build fails during kernel compilation:**
- Ensure all dependencies are installed
- Check you have enough RAM (2GB+ recommended)

**QEMU doesn't start:**
- Verify both kernel and initramfs exist:
  ```bash
  ls build/linux/arch/x86/boot/bzImage
  ls output/initramfs.cpio
  ```

**System boots but hangs:**
- Check `/etc/init.d/rcS` is executable
- Verify required libraries are copied to rootfs

**Kernel panic on boot:**
- Try different kernel parameters in `scripts/run-qemu.sh`
- Add/remove `noapic acpi=off` as needed

## 📚 Learning Resources

- [Linux From Scratch](http://www.linuxfromscratch.org/)
- [ToyBox Documentation](http://landley.net/toybox/)
- [Linux Kernel Documentation](https://www.kernel.org/doc/html/latest/)
- [initramfs explanation](https://wiki.debian.org/initramfs)

## 🤝 Contributing

Contributions are welcome! Some ideas:
- Add more init scripts (networking, services)
- Create UEFI boot support
- Add more custom applications
- Improve QEMU configuration
- Documentation improvements
- Package manager integration

## 📜 License

- **NeonBitOS original code**: Public Domain (The Unlicense)
- **Linux kernel**: GPL-2.0
- **ToyBox**: 0BSD
- **Termrex**: MIT
- **pidigits**: Public Domain

See [LICENSE](LICENSE) for details.

## 🌟 Acknowledgments

- [Linus Torvalds](https://github.com/torvalds) and the Linux kernel team
- [Rob Landley](http://landley.net/) for ToyBox
- [Satya Prakash Dahal](https://github.com/SATYADAHAL/) for Termrex
- The open source community

---

**NeonBitOS** - *Where minimal meets cyberpunk* ⚡🔮
