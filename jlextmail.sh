#!/bin/bash

git send-email --from hongbo.wang@nxp.com \
 --to jailhouse-dev@googlegroups.com \
 --to jan.kiszka@siemens.com \
 --to mingkai.hu@nxp.com \
 --to xiaobo.xie@nxp.com \
 --to jiafei.pan@nxp.com \
 --to hongbo.wang@nxp.com \
 ./0205_ok/*.patch
