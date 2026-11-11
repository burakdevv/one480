/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_ENGINE_H
#define ONE480_ENGINE_H
#include "../hs/main.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct one480_engine one480_engine;
one480_engine *one480_engine_create(const char *quarantine_dir,const one480_callbacks *callbacks);
void one480_engine_destroy(one480_engine *engine);
one480_status one480_engine_scan(one480_engine *engine,const char *path,one480_scan_summary *summary);
one480_status one480_engine_scan_cancel(one480_engine *engine);
one480_status one480_engine_quarantine(one480_engine *engine,const char *path,const char *reason,char *id_out,size_t id_capacity);
#ifdef __cplusplus
}
#endif
#endif
