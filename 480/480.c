/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "480.h"
#include <stdlib.h>
#include <string.h>
struct one480_engine { char quarantine[32768]; one480_callbacks cb; volatile int cancel; };
const char *one480_status_string(one480_status s) {
 switch(s){case ONE480_OK:return "OK";case ONE480_E_INVALID_ARGUMENT:return "Invalid argument";
 case ONE480_E_IO:return "I/O error";case ONE480_E_MEMORY:return "Out of memory";
 case ONE480_E_NOT_FOUND:return "Not found";case ONE480_E_ACCESS:return "Access denied";
 case ONE480_E_CANCELLED:return "Cancelled";case ONE480_E_LIMIT:return "Limit exceeded";
 case ONE480_E_UNSUPPORTED:return "Unsupported";default:return "Internal error";}
}
one480_engine *one480_engine_create(const char *q,const one480_callbacks *cb) {
 if(!q||!*q)return NULL; one480_engine *e=(one480_engine*)calloc(1,sizeof(*e)); if(!e)return NULL;
 if(strlen(q)>=sizeof(e->quarantine)){free(e);return NULL;} strcpy(e->quarantine,q); if(cb)e->cb=*cb; return e;
}
void one480_engine_destroy(one480_engine *e){if(e){memset(e,0,sizeof(*e));free(e);}}
one480_status one480_engine_scan_cancel(one480_engine *e){if(!e)return ONE480_E_INVALID_ARGUMENT;e->cancel=1;return ONE480_OK;}
one480_status one480_engine_scan(one480_engine *e,const char *path,one480_scan_summary *s) {
 if(!e||!path||!s)return ONE480_E_INVALID_ARGUMENT; memset(s,0,sizeof(*s));
 if(e->cancel){s->cancelled=1;return ONE480_E_CANCELLED;}
 if(e->cb.log)e->cb.log(ONE480_LOG_INFO,"Scan request accepted; use the Qt scanner for recursive traversal.",e->cb.user_data);
 if(e->cb.progress)e->cb.progress(path,0,1,e->cb.user_data);
 s->seen=1;s->skipped=1;
 if(e->cb.log)e->cb.log(ONE480_LOG_WARNING,"Native C core is a safe API shell; detailed scanning is provided by the Qt adapter.",e->cb.user_data);
 return ONE480_OK;
}
one480_status one480_engine_quarantine(one480_engine *e,const char *p,const char *r,char *id,size_t cap) {
 (void)e;(void)p;(void)r;(void)id;(void)cap;
 /* Quarantine is implemented in the Qt adapter with atomic rename + metadata. */
 return ONE480_E_UNSUPPORTED;
}
