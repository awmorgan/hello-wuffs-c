#!/bin/bash -eu
# Copyright 2019 The Wuffs Authors.
#
# Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
# https://www.apache.org/licenses/LICENSE-2.0> or the MIT license
# <LICENSE-MIT or https://opensource.org/licenses/MIT>, at your
# option. This file may not be copied, modified, or distributed
# except according to those terms.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT

# ----------------

CC=${CC:-gcc}

# You may need to run
#   go install github.com/google/wuffs/cmd/wuffs-c
# beforehand, to install the wuffs-c compiler.
mkdir -p build/gen
wuffs-c gen -package_name base > build/gen/wuffs-base.c
wuffs-c gen -package_name demo < parse.wuffs > build/gen/parse.c

echo --- C Implementation Prints ---
$CC main.c naive-parse.c -o build/n.out
./build/n.out

echo ------ Wuffs Impl Prints ------
$CC main.c wuffs-parse.c -o build/w.out
./build/w.out
