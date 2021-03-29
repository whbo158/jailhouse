#!/bin/bash

cd ..

insmod jailhouse.ko;

./jailhouse disable

./jailhouse enable imx8mp.cell;
./jailhouse cell linux imx8mp-linux-demo.cell -i ./rootfs.cpio.gz ./Image-imx -d ./inmate-imx8mp-evk.dtb -c "clk_ignore_unused console=ttymxc3,115200 earlycon=ec_imx6q,0x30890000,115200"

