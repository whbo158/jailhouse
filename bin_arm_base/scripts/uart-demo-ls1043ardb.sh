#!/bin/bash

cd ..

insmod jailhouse.ko;

./jailhouse disable

./jailhouse enable ls1043a-rdb.cell;
./jailhouse cell create ls1043a-rdb-inmate-demo.cell;
./jailhouse cell load 1 ./uart-demo.bin
./jailhouse cell start 1

