/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_EXESREAD_H
#define ONE480_EXESREAD_H
#include <stddef.h>
#include <stdint.h>
typedef struct one480_pe_section { char name[9]; uint32_t virtual_size,virtual_address,raw_size,raw_offset,characteristics; double entropy; } one480_pe_section;
typedef struct one480_pe_report { int is_pe,is_64bit; uint16_t machine,section_count; double heuristic_score; one480_pe_section *sections; size_t count; } one480_pe_report;
int one480_pe_analyze(const uint8_t *data,size_t length,one480_pe_report *report);
void one480_pe_report_dispose(one480_pe_report *report);
#endif
