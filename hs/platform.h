/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_PLATFORM_H
#define ONE480_PLATFORM_H
#if defined(_WIN32)
#define ONE480_WINDOWS 1
#else
#define ONE480_WINDOWS 0
#endif
#ifdef __cplusplus
extern "C" {
#endif
int one480_platform_is_critical_path(const char *utf8_path);
#ifdef __cplusplus
}
#endif
#endif
