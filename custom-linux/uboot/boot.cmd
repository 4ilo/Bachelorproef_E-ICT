echo test
fatload mmc 0 0x12000000 zImage
fatload mmc 0 0x18000000 dts/test.dtb
setenv bootargs "console=ttymxc1,115200 root=/dev/mmcblk0p2 rootwait panic=10"
bootz 0x12000000 - 0x18000000


## build met mkimage -T script -C none -A arm -n 'SoM9260 Load Script' -d boot.cmd boot.scr