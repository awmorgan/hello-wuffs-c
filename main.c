// Copyright 2019 The Wuffs Authors.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// https://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or https://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#define WUFFS_CONFIG__MODULE__BASE
#define WUFFS_IMPLEMENTATION
#include "./build/gen/parse.c"

uint32_t parse(char *p, size_t n) {
  wuffs_base__status status;
  wuffs_demo__parser parser;

  status = wuffs_demo__parser__initialize(&parser, sizeof__wuffs_demo__parser(),
                                          WUFFS_VERSION, 0);
  if (!wuffs_base__status__is_ok(&status)) {
    printf("initialize: %s\n", wuffs_base__status__message(&status));
    return 0;
  }

  wuffs_base__io_buffer iobuf =
      wuffs_base__ptr_u8__reader((uint8_t *)p, n, true);

  status = wuffs_demo__parser__parse(&parser, &iobuf);
  if (!wuffs_base__status__is_ok(&status)) {
    printf("parse: %s\n", wuffs_base__status__message(&status));
    return 0;
  }

  return wuffs_demo__parser__value(&parser);
}

int main(int argc, char **argv) {
  uint32_t i;
  printf( "%" PRIu32 "\n", parse("0", sizeof("0")));
  printf( "%" PRIu32 "\n", parse("12", sizeof("12")));
  printf( "%" PRIu32 "\n", parse("56789", sizeof("56789")));
  printf( "%" PRIu32 "\n", parse("4294967290", sizeof("4294967290")));
  printf( "%" PRIu32 "\n", parse("4294967295", sizeof("4294967295"))); // (1<<32) - 1, aka UINT32_MAX.
  printf( "%" PRIu32 "\n", parse("4294967296", sizeof("4294967296"))); // (1<<32).
  printf( "%" PRIu32 "\n", parse("123456789012", sizeof("123456789012")));
  return 0;
}
