/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "../hs/main.h"
#include <assert.h>
#include <string.h>
int main(void){assert(strcmp(one480_status_string(ONE480_OK),"OK")==0);assert(ONE480_DETECTED>ONE480_CLEAN);return 0;}
