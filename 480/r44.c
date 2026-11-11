/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "../hs/dots.h"
#include "../hs/main.h"
#include <stdlib.h>
#include <string.h>
/* Signature database parser: deliberately accepts only the documented bounded O480SIG header.
   Full signature distribution is intentionally user-supplied; no remote feed is trusted. */
typedef struct one480_sig_header { char magic[8]; uint32_t version,count; } one480_sig_header;
int one480_signature_header_validate(const void *data,size_t length){
 if(!data||length<sizeof(one480_sig_header))return 0;
 const one480_sig_header *h=(const one480_sig_header*)data;
 return memcmp(h->magic,ONE480_SIGNATURE_MAGIC,7)==0 && h->version==1 && h->count<=ONE480_MAX_SIGNATURES;
}
