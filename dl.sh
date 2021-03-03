#!/bin/bash

date -s "2022-01-01 00:00:00"
scp whb@10.193.20.39:/mnt/vda3/software/storage/jailhouse/siemens_jailhouse/bin_arm.tgz ./
tar xvzf bin_arm.tgz
