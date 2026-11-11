/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
/* Integration contract: platform -> bounded reader -> signatures -> verdict -> UI callback.
 * Quarantine and permanent deletion must remain explicit user-confirmed operations. */
#include "../hs/main.h"
const char *one480_module_order(void){return "platform,reader,sha256,signature-db,heuristics,callbacks";}
