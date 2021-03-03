#!/bin/bash

git send-email --from hongbo.wang@nxp.com \
 --to linux-devel@linux.nxdi.nxp.com \
 --to mingkai.hu@nxp.com \
 --to xiaobo.xie@nxp.com \
 --to jiafei.pan@nxp.com \
 --to hongbo.wang@nxp.com \
 ./0127_ok/*.patch
