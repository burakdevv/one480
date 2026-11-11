/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_SYSTEM_H
#define ONE480_SYSTEM_H
#include "main.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct one480_file_info { uint64_t size; int is_directory; int is_regular; } one480_file_info;
one480_status one480_system_stat(const char *path, one480_file_info *out_info);
#ifdef __cplusplus
}
#endif
#endif
