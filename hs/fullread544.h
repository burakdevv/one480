/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_FULLREAD544_H
#define ONE480_FULLREAD544_H
#include <stddef.h>
#include <stdint.h>
typedef struct one480_buffer { uint8_t *data; size_t length; } one480_buffer;
int one480_read_file(const char *path,uint64_t limit,one480_buffer *out);
void one480_buffer_dispose(one480_buffer *buffer);
#endif
