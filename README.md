# CuseErrorKernelModuleFix
Implements the module to load and help the Major Number Errors that Steam throws at you on Game Crashes, hopefully.
``` dmesg | tail```
# To see whats going wrong.

```dmesg```
# Shows all processes going right or wrong.

Helps the Text Blocks. 

# Instructions 
🧵 my_cuse_device Kernel Module

A simple Linux character device module that dynamically allocates a major number and responds to open, read, and write calls. This module creates a /dev/my_cuse_device file that allows user-space applications to exchange text with kernel space through a fixed-size buffer.
# Folder Contents

Kernel
my_module.c 
Kernel module
source code
Makefile       
Kernel
build
Makefile
---------------------------------------------------------------------
# 🛠️ Requirements

    Raspberry Pi or ARM-based Linux

    Linux headers for your current kernel version

    make, gcc, and kernel build tools

Install dependencies (if not present):

``` sudo apt install raspberrypi-kernel-headers build-essential ```
-----------------------------------------------------------------------
# 🚀 How to Build & Load the Module

From inside the Kernel/ directory:

``` make clean ```
``` make ```
``` sudo insmod my_module.ko ```

# Then check the allocated major number:
dmesg | grep "Allocated Major"

Supposed to show a number like 509
``` Allocated Major: 509, Minor: 0```
sudo mknod /dev/my_cuse_device c 509 0
sudo chmod 666 /dev/my_cuse_device
# Replace 509 with the actually number found in dmesg | tail

# Check and see if the kernel module responds to workloads or a simple echo "hello world" etc.
``` echo "Hello Kernel" > /dev/my_cuse_device```
```cat /dev/my_cuse_device```

Expected output
```Hello Kernel```
in dmesg it should say the module is opened
there shouldn't be anything null, or have any read, write errors.

And in kernel logs:

dmesg | tail
```# my_cuse_device opened```

#🔄 Unload the Module

```sudo rmmod my_module```

# To check cleanup:

```dmesg | tail```
# Device unregistered




