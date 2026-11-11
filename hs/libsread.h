/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_LIBSREAD_H
#define ONE480_LIBSREAD_H
#include <stddef.h>
#include <stdint.h>
typedef struct one480_archive_entry { char name[256]; uint64_t offset,size; } one480_archive_entry;
typedef struct one480_archive_index { one480_archive_entry *entries; size_t count; int kind; } one480_archive_index;
int one480_archive_index_memory(const uint8_t *data,size_t length,one480_archive_index *out_index);
void one480_archive_index_dispose(one480_archive_index *index);
#endif
