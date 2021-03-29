#!/bin/bash

cd ..

insmod jailhouse.ko;

./jailhouse disable

./jailhouse enable imx8mp.cell;
./jailhouse cell create imx8mp-inmate-demo.cell;
./jailhouse cell load 1 ./gic-demo.bin
./jailhouse cell start 1

