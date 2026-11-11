/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "../hs/platform.h"
#include <string.h>
#if ONE480_WINDOWS
#include <windows.h>
#endif
int one480_platform_is_critical_path(const char *p){
 if(!p)return 1;
#if ONE480_WINDOWS
 char win[MAX_PATH]={0}; if(GetWindowsDirectoryA(win,MAX_PATH)>0){
  size_t n=strlen(win); if(_strnicmp(p,win,n)==0)return 1;
 }
#else
 if(strncmp(p,"/etc/",5)==0||strncmp(p,"/usr/",5)==0||strncmp(p,"/bin/",5)==0)return 1;
#endif
 return 0;
}
