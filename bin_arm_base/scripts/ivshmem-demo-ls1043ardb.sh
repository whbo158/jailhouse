#!/bin/bash

cd ..

insmod jailhouse.ko;

./jailhouse disable

./jailhouse enable ls1043a-rdb.cell;
./jailhouse cell create ls1043a-rdb-inmate-demo.cell;
./jailhouse cell load 1 ./ivshmem-demo.bin
./jailhouse cell start 1
./ivshmem-demo -d /dev/uio0 -t 1

