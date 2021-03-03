#!/bin/bash

cd ..

insmod jailhouse.ko;

./jailhouse disable

./jailhouse enable ls1046a-rdb.cell;
./jailhouse cell create ls1046a-rdb-inmate-demo.cell;
./jailhouse cell load 1 ./uart-demo.bin
./jailhouse cell start 1

