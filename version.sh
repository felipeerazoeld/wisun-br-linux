#!/bin/sh
# SPDX-License-Identifier: GPL-2.0
#
# Copyright 2017-2021, Silicon Laboratories, Inc.

SRC_DIR=$1
VERSION_FILE=$2
GIT_LABEL="$(git -C $SRC_DIR describe --tags --dirty --match "*v[0-9]*" || echo '<unknown version>')"

cat << EOF > $VERSION_FILE.tmp
/* SPDX-License-Identifier: GPL-2.0 */
/* THIS FILE IS AUTOMATICALLY GENERATED. DO NOT EDIT! */
#include <stdint.h>
#include "common/version.h"

const char *version_daemon_str = "${GIT_LABEL}";
uint32_t version_daemon_api = VERSION(0, 0, 0);

const char *version_hwsim_str = "hwsim-${GIT_LABEL}";
uint32_t version_hwsim = VERSION(0, 0, 0);
uint32_t version_hwsim_api = VERSION(0, 10, 0);
EOF

if cmp -s $VERSION_FILE $VERSION_FILE.tmp
then
    rm -f $VERSION_FILE.tmp
else
    mv -f $VERSION_FILE.tmp  $VERSION_FILE
fi
