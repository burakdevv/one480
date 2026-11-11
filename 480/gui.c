/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "../hs/main.h"
void one480_gui_log_bridge(one480_log_callback cb,one480_log_level level,const char *msg,void *ctx){
 if(cb&&msg)cb(level,msg,ctx);
}
