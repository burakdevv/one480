/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_DLLSREAD_H
#define ONE480_DLLSREAD_H
#include <stddef.h>
#include <stdint.h>
typedef struct one480_pe_import { char library[256]; char symbol[256]; uint16_t ordinal; int by_ordinal; } one480_pe_import;
typedef struct one480_pe_import_table { one480_pe_import *items; size_t count; } one480_pe_import_table;
int one480_pe_read_imports(const uint8_t *data,size_t length,one480_pe_import_table *out_table);
void one480_pe_import_table_dispose(one480_pe_import_table *table);
#endif
