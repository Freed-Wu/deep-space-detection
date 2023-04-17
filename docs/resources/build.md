# How to Build

## Dependencies

- [minicom](https://archlinux.org/packages/extra/x86_64/minicom) or
  [picocom](https://archlinux.org/packages/extra/x86_64/picocom): Serial debug helper
- [petalinux](https://aur.archlinux.org/packages/petalinux)
- `/the/path/of/system.xsa`: provided by your FPGA engineer

## Build

<!-- markdownlint-disable MD013 -->

```bash
petalinux-create -t project -n soc --template zynqMP
cd soc
cp /the/path/of/system.xsa project-spec/hw-description
petalinux-config  # see Configure
petalinux-config -c rootfs  # see Configure
# {{{
petalinux-create -t apps -n autostart --enable
rm -r project-spec/meta-user/recipes-apps/autostart
cp /the/path/of/this/project project-spec/meta-user/recipes-apps/autostart
# }}}
# or: (it will fix git version)
# petalinux-create -t apps -n autostart --enable -s /the/path/of/this/project
cp project-spec/meta-user/recipes-apps/autostart/examples/project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi project-spec/meta-user/recipes-bsp/device-tree/files
cp project-spec/meta-user/recipes-apps/autostart/examples/project-spec/meta-user/recipes-extended project-spec/meta-user
# on the first time it costs about 1 hour while it costs 2.5 minutes later
petalinux-build
petalinux-package --boot --u-boot --fpga
# insert SD card to your PC, assume your SD card has 2 part: BOOT (vfat) and root (ext4)
cp images/linux/image.ub images/linux/BOOT.BIN images/linux/boot.scr /run/media/$USER/BOOT
# use sudo to avoid wrong privilege
sudo rm -r /run/media/$USER/root/*
sudo tar vxaCf /run/media/$USER/root images/linux/rootfs.tar.gz
# or wait > 10 seconds to sync automatically
sync
# insert SD card to your board
# open serial debug helper
# assume your COM port is /dev/ttyUSB1
minicom -D /dev/ttyUSB1
# reset
```

<!-- markdownlint-enable MD013 -->

## Configure

All configurations are advised.

### `petalinux-config`

- Image Packaging Configuration -> Root filesystem type -> EXT4 (SD/eMMC/SATA/USB)
- Image Packaging Configuration -> Device node of SD device -> /dev/mmcblk1p2
- Linux Components Selection -> u-boot -> ext-local-src
- Linux Components Selection -> External u-boot local source settings ->
  External u-boot local source path ->
  /the/path/of/downloaded/github.com/Xilinx/u-boot-xlnx
- Linux Components Selection -> linux-kernel -> ext-local-src
- Linux Components Selection -> External linux-kernel local source settings ->
  External linux-kernel local source path ->
  /the/path/of/downloaded/github.com/Xilinx/linux-xlnx
- Yocto Settings -> Add pre-mirror url -> pre-mirror url path ->
  file:///the/path/of/downloaded/downloads
- Yocto Settings -> Local sstate feeds settings -> local sstate feeds url ->
  /the/path/of/downloaded/sstate-cache/of/aarch64

### `petalinux-config -c rootfs`

- Image Features -> serial-autologin-root
- Image Features -> package-management

### References

- [petalinux-tools-reference-guide](https://docs.xilinx.com/r/en-US/ug1144-petalinux-tools-reference-guide/Menuconfig-Corruption-for-Kernel-and-U-Boot)
- [Embedded-Design-Tutorials](https://xilinx.github.io/Embedded-Design-Tutorials/docs/2021.2/build/html/docs/Introduction/ZynqMPSoC-EDT/1-introduction.html)
- [PetaLinux Yocto Tips](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842475/PetaLinux+Yocto+Tips)
