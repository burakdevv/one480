/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "../hs/main.h"
/* C ABI boundary: no Qt types cross the engine API.
 * Callback strings are UTF-8 and valid only for the duration of the callback. */
const unsigned one480_abi_version(void){return 1u;}
