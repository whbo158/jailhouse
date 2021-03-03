#!/bin/bash

cd ..

insmod jailhouse.ko;

./jailhouse disable

./jailhouse enable ls1046a-rdb.cell;
./jailhouse cell create ls1046a-rdb-inmate-demo.cell;
./jailhouse cell load 1 ./ivshmem-demo.bin
./jailhouse cell start 1
./ivshmem-demo -d /dev/uio0 -t 1

