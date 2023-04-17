# deep-space-detection

[![readthedocs](https://shields.io/readthedocs/deep-space-detection)](https://deep-space-detection.readthedocs.io)
[![pre-commit.ci status](https://results.pre-commit.ci/badge/github/Freed-Wu/deep-space-detection/main.svg)](https://results.pre-commit.ci/latest/github/Freed-Wu/deep-space-detection/main)
[![github/workflow](https://github.com/Freed-Wu/deep-space-detection/actions/workflows/main.yml/badge.svg)](https://github.com/Freed-Wu/deep-space-detection/actions)
[![codecov](https://codecov.io/gh/Freed-Wu/deep-space-detection/branch/main/graph/badge.svg)](https://codecov.io/gh/Freed-Wu/deep-space-detection)
[![DeepSource](https://deepsource.io/gh/Freed-Wu/deep-space-detection.svg/?show_trend=true)](https://deepsource.io/gh/Freed-Wu/deep-space-detection)

[![github/downloads](https://shields.io/github/downloads/Freed-Wu/deep-space-detection/total)](https://github.com/Freed-Wu/deep-space-detection/releases)
[![github/downloads/latest](https://shields.io/github/downloads/Freed-Wu/deep-space-detection/latest/total)](https://github.com/Freed-Wu/deep-space-detection/releases/latest)
[![github/issues](https://shields.io/github/issues/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/issues)
[![github/issues-closed](https://shields.io/github/issues-closed/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/issues?q=is%3Aissue+is%3Aclosed)
[![github/issues-pr](https://shields.io/github/issues-pr/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/pulls)
[![github/issues-pr-closed](https://shields.io/github/issues-pr-closed/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/pulls?q=is%3Apr+is%3Aclosed)
[![github/discussions](https://shields.io/github/discussions/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/discussions)
[![github/milestones](https://shields.io/github/milestones/all/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/milestones)
[![github/forks](https://shields.io/github/forks/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/network/members)
[![github/stars](https://shields.io/github/stars/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/stargazers)
[![github/watchers](https://shields.io/github/watchers/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/watchers)
[![github/contributors](https://shields.io/github/contributors/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/graphs/contributors)
[![github/commit-activity](https://shields.io/github/commit-activity/w/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/graphs/commit-activity)
[![github/last-commit](https://shields.io/github/last-commit/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/commits)
[![github/release-date](https://shields.io/github/release-date/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/releases/latest)

[![github/license](https://shields.io/github/license/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection/blob/main/LICENSE)
[![github/languages](https://shields.io/github/languages/count/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection)
[![github/languages/top](https://shields.io/github/languages/top/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection)
[![github/directory-file-count](https://shields.io/github/directory-file-count/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection)
[![github/code-size](https://shields.io/github/languages/code-size/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection)
[![github/repo-size](https://shields.io/github/repo-size/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection)
[![github/v](https://shields.io/github/v/release/Freed-Wu/deep-space-detection)](https://github.com/Freed-Wu/deep-space-detection)

Deploy a model to AMD Xilinx ZynqMP UltraScale+.

## Dependencies

- [minicom](https://archlinux.org/packages/extra/x86_64/minicom) or
  [picocom](https://archlinux.org/packages/extra/x86_64/picocom): Serial debug helper
- [petalinux](https://aur.archlinux.org/packages/petalinux)
- `/the/path/of/system.xsa`: provided by your FPGA engineer

## Build

<!-- markdownlint-disable MD013 -->

```bash
cd /the/parent/path/of/project
petalinux-create -t project -n demo --template zynqMP
cd demo
cp /the/path/of/system.xsa project-spec/hw-description/system.xsa
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
# on the first time it costs about 1 hour while it costs 2.5 minutes later
petalinux-build
# insert SD card to your PC, assume your SD card has 2 part: BOOT (vfat) and root (ext4)
cp images/linux/image.ub images/linux/BOOT.BIN images/linux/boot.scr /run/media/$USER/BOOT
# use sudo to avoid wrong privilege
sudo rm -r /run/media/$USER/root/*
sudo tar vxaCf /run/media/$USER/root images/linux/rootfs.tar.gz
# or wait > 10 seconds to sync automatically
cd /run/media/$USER/root
sync
cd -
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
- user packages -> autostart

## Documents

- [petalinux-tools-reference-guide](https://docs.xilinx.com/r/en-US/ug1144-petalinux-tools-reference-guide/Menuconfig-Corruption-for-Kernel-and-U-Boot)
- [Embedded-Design-Tutorials](https://xilinx.github.io/Embedded-Design-Tutorials/docs/2021.2/build/html/docs/Introduction/ZynqMPSoC-EDT/1-introduction.html)
- [PetaLinux Yocto Tips](https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842475/PetaLinux+Yocto+Tips)
- [软件设计报告大纲](https://github.com/Freed-Wu/deep-space-detection/blob/main/docs/index.md)
