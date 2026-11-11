/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "../hs/system.h"
#include <string.h>
#if ONE480_WINDOWS
#include <windows.h>
#else
#include <sys/stat.h>
#endif
one480_status one480_system_stat(const char *p,one480_file_info *o){
 if(!p||!o)return ONE480_E_INVALID_ARGUMENT; memset(o,0,sizeof(*o));
#if ONE480_WINDOWS
 WIN32_FILE_ATTRIBUTE_DATA d; if(!GetFileAttributesExA(p,GetFileExInfoStandard,&d))return ONE480_E_NOT_FOUND;
 o->is_directory=(d.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)!=0;
 o->is_regular=!o->is_directory; o->size=((uint64_t)d.nFileSizeHigh<<32)|d.nFileSizeLow;
#else
 struct stat st; if(stat(p,&st)!=0)return ONE480_E_NOT_FOUND;
 o->is_directory=S_ISDIR(st.st_mode);o->is_regular=S_ISREG(st.st_mode);o->size=(uint64_t)st.st_size;
#endif
 return ONE480_OK;
}
