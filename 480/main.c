/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "480.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv){
 if(argc<3||strcmp(argv[1],"--scan")!=0){fprintf(stderr,"one480-cli %s\nUsage: one480-cli --scan <path>\n",ONE480_VERSION);return 2;}
 one480_callbacks cb={0}; one480_engine *e=one480_engine_create(".one480-quarantine",&cb);
 if(!e){fprintf(stderr,"Engine initialization failed\n");return 1;}
 one480_scan_summary s; one480_status rc=one480_engine_scan(e,argv[2],&s); one480_engine_destroy(e);
 if(rc!=ONE480_OK){fprintf(stderr,"%s\n",one480_status_string(rc));return 1;}
 printf("Requests: %llu; skipped: %llu\n",(unsigned long long)s.seen,(unsigned long long)s.skipped);return 0;
}
