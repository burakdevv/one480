/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#if defined(_WIN32)
#include <windows.h>
const char *one480_windows_api_groups(void){return "Kernel32: file metadata and file I/O; Shell32: optional shell integration; Advapi32: version-independent OS metadata";}
#else
const char *one480_windows_api_groups(void){return "Not a Windows build";}
#endif
