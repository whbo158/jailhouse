#!/bin/bash

cd ..

insmod jailhouse.ko;

./jailhouse disable

./jailhouse enable ls1043a-rdb.cell;
./jailhouse cell linux ls1043a-rdb-dpaa-linux-demo.cell -i ./rootfs.cpio.gz ./Image -d ./inmate-ls1043a-rdb-dpaa.dtb -c "console=ttyS0,115200 earlycon=uart8250,mmio,0x21c0600"

