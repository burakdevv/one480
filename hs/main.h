/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_MAIN_H
#define ONE480_MAIN_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#define ONE480_VERSION "1.0.0"
#define ONE480_SHA256_SIZE 32
typedef enum one480_status {
 ONE480_OK=0, ONE480_E_INVALID_ARGUMENT, ONE480_E_IO, ONE480_E_MEMORY,
 ONE480_E_NOT_FOUND, ONE480_E_ACCESS, ONE480_E_CANCELLED, ONE480_E_LIMIT,
 ONE480_E_UNSUPPORTED, ONE480_E_INTERNAL
} one480_status;
typedef enum one480_verdict {
 ONE480_CLEAN=0, ONE480_SUSPICIOUS, ONE480_DETECTED, ONE480_SKIPPED, ONE480_ERROR
} one480_verdict;
typedef enum one480_log_level { ONE480_LOG_INFO=0, ONE480_LOG_WARNING, ONE480_LOG_ERROR } one480_log_level;
typedef void (*one480_log_callback)(one480_log_level,const char*,void*);
typedef void (*one480_progress_callback)(const char*,uint64_t,uint64_t,void*);
typedef struct one480_callbacks {
 one480_log_callback log;
 one480_progress_callback progress;
 void *user_data;
} one480_callbacks;
typedef struct one480_scan_result {
 one480_verdict verdict;
 char sha256[65];
 char detection[128];
 char path[32768];
 uint64_t size;
} one480_scan_result;
typedef struct one480_scan_summary {
 uint64_t seen, scanned, clean, suspicious, detected, skipped, errors;
 int cancelled;
} one480_scan_summary;
const char *one480_status_string(one480_status status);
#ifdef __cplusplus
}
#endif
#endif
