/*
 * SPDX-License-Identifier: MIT
 *
 * MIT Lisansı / MIT License
 * Telif Hakkı / Copyright (c) 2026 one480 katkıda bulunanlar / contributors
 *
 * Bu yazılım MIT Lisansı kapsamında özgürce kullanılabilir.
 * Lisansın tam metni için projenin kök dizinindeki LICENSE dosyasına bakın.
 * This software may be freely used under the MIT License.
 * See the LICENSE file in the project root for the full license text.
 */

/**
 * @file platform.h
 * @brief Derleme zamanı platform, derleyici ve mimari saptama makroları.
 *        Compile-time platform, compiler, and architecture detection macros.
 *
 * Bu dosya bağımlılık zincirinin en altında yer alır; başka one480
 * başlığı dahil etmez. Tüm kaynak dosyalar tarafından dolaylı olarak
 * main.h üzerinden çekilir.
 *
 * This file sits at the bottom of the include chain; it includes no
 * other one480 headers. All source files pull it indirectly via main.h.
 */

#ifndef ONE480_PLATFORM_H
#define ONE480_PLATFORM_H

/* =========================================================
 * DERLEYICI SAPTAMA / COMPILER DETECTION
 * ========================================================= */

#if defined(_MSC_VER)
#   define ONE480_MSVC 1
    /** MSVC sürüm numarası (örn. 1930 = VS 2022 17.0).
     *  MSVC version number (e.g. 1930 = VS 2022 17.0). */
#   define ONE480_COMPILER_VER  _MSC_VER
#elif defined(__clang__)
#   define ONE480_CLANG 1
#   define ONE480_COMPILER_VER  (__clang_major__ * 10000 \
                                + __clang_minor__ * 100  \
                                + __clang_patchlevel__)
#elif defined(__GNUC__)
#   define ONE480_GCC 1
#   define ONE480_COMPILER_VER  (__GNUC__ * 10000 \
                                + __GNUC_MINOR__ * 100 \
                                + __GNUC_PATCHLEVEL__)
#else
#   error "Desteklenmeyen derleyici. / Unsupported compiler."
#endif

/* =========================================================
 * İŞLETİM SİSTEMİ SAPTAMA / OS DETECTION
 * ========================================================= */

#if defined(_WIN32) || defined(_WIN64)
#   define ONE480_WINDOWS 1
#elif defined(__linux__)
#   define ONE480_LINUX 1
#elif defined(__APPLE__)
#   define ONE480_MACOS 1
#else
#   error "Desteklenmeyen platform. / Unsupported platform."
#endif

/* =========================================================
 * MİMARİ SAPTAMA / ARCHITECTURE DETECTION
 * ========================================================= */

#if defined(_M_X64) || defined(__x86_64__)
#   define ONE480_X64 1
#elif defined(_M_IX86) || defined(__i386__)
#   define ONE480_X86 1
#elif defined(_M_ARM64) || defined(__aarch64__)
#   define ONE480_ARM64 1
#else
#   define ONE480_ARCH_UNKNOWN 1
#endif

/* =========================================================
 * WINDOWS BAŞLIK ÖN TANIMLARI / WINDOWS HEADER PREREQUISITES
 * Bu tanımlar <windows.h> dahil edilmeden önce ayarlanmalıdır.
 * These defines must be set before including <windows.h>.
 * ========================================================= */

#ifdef ONE480_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   ifndef UNICODE
#       define UNICODE
#   endif
#   ifndef _UNICODE
#       define _UNICODE
#   endif
    /* Windows 10+ hedefle / Target Windows 10+ */
#   ifndef WINVER
#       define WINVER       0x0A00
#   endif
#   ifndef _WIN32_WINNT
#       define _WIN32_WINNT 0x0A00
#   endif
    /* VC++ çalışma zamanı güvenli CRT uyarılarını susturma
     * Suppress VC++ secure CRT deprecation warnings */
#   ifndef _CRT_SECURE_NO_WARNINGS
#       define _CRT_SECURE_NO_WARNINGS
#   endif
#endif /* ONE480_WINDOWS */

/* =========================================================
 * API İHRACAT / API EXPORT DECORATION
 * Statik kütüphane olarak derleniyor; dekorasyon gerekmez.
 * Built as a static library; no decoration needed.
 * ========================================================= */

#define ONE480_API        /* boş — statik lib / empty — static lib */
#define ONE480_INTERNAL   /* iç kullanım işareti (belgesel) / internal use marker */

/* =========================================================
 * SATIR İÇİ / INLINE
 * ========================================================= */

#if defined(ONE480_MSVC)
#   define ONE480_INLINE     __forceinline
#   define ONE480_NOINLINE   __declspec(noinline)
#elif defined(ONE480_GCC) || defined(ONE480_CLANG)
#   define ONE480_INLINE     __attribute__((always_inline)) static inline
#   define ONE480_NOINLINE   __attribute__((noinline))
#else
#   define ONE480_INLINE     static inline
#   define ONE480_NOINLINE
#endif

/* =========================================================
 * KISITLAMA / RESTRICT
 * ========================================================= */

#if defined(ONE480_MSVC)
#   define ONE480_RESTRICT  __restrict
#elif defined(ONE480_GCC) || defined(ONE480_CLANG)
#   define ONE480_RESTRICT  __restrict__
#else
#   define ONE480_RESTRICT
#endif

/* =========================================================
 * DAL TAHMİNİ / BRANCH PREDICTION HINTS
 * ========================================================= */

#if defined(ONE480_GCC) || defined(ONE480_CLANG)
    /** Koşulun çoğunlukla doğru olduğunu belirtir.
     *  Hints that the condition is usually true. */
#   define ONE480_LIKELY(x)   __builtin_expect(!!(x), 1)
    /** Koşulun çoğunlukla yanlış olduğunu belirtir.
     *  Hints that the condition is usually false. */
#   define ONE480_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#   define ONE480_LIKELY(x)   (x)
#   define ONE480_UNLIKELY(x) (x)
#endif

/* =========================================================
 * KULLANILMAYAN DEĞİŞKEN / SUPPRESS UNUSED VARIABLE WARNING
 * ========================================================= */

/** Kasıtlı olarak kullanılmayan parametre veya değişken.
 *  Marks an intentionally unused parameter or variable. */
#define ONE480_UNUSED(x)   ((void)(x))

/* =========================================================
 * DÖNDÜRMEZ / NORETURN
 * ========================================================= */

#if defined(ONE480_MSVC)
#   define ONE480_NORETURN  __declspec(noreturn)
#elif defined(ONE480_GCC) || defined(ONE480_CLANG)
#   define ONE480_NORETURN  __attribute__((noreturn))
#else
#   define ONE480_NORETURN
#endif

/* =========================================================
 * PRINTF BİÇİM ÖZELLİĞİ / PRINTF FORMAT ATTRIBUTE
 * ========================================================= */

#if defined(ONE480_GCC) || defined(ONE480_CLANG)
    /** fmt_idx: biçim dizesi konumu (1'den başlar).
     *  fmt_idx: position of format string (1-based).
     *  arg_idx: ilk değişken argüman konumu.
     *  arg_idx: position of first variadic argument. */
#   define ONE480_PRINTF_FMT(fmt_idx, arg_idx) \
        __attribute__((format(printf, fmt_idx, arg_idx)))
#else
#   define ONE480_PRINTF_FMT(fmt_idx, arg_idx)
#endif

/* =========================================================
 * STATİK DOĞRULAMA / STATIC ASSERTION  (C11 / C++11)
 * ========================================================= */

#ifdef __cplusplus
#   define ONE480_STATIC_ASSERT(cond, msg)  static_assert(cond, msg)
#else
#   define ONE480_STATIC_ASSERT(cond, msg)  _Static_assert(cond, msg)
#endif

/* =========================================================
 * KULLANIMSIZ BİÇİM / DEPRECATED ATTRIBUTE
 * ========================================================= */

#if defined(ONE480_MSVC)
#   define ONE480_DEPRECATED(msg) __declspec(deprecated(msg))
#elif defined(ONE480_GCC) || defined(ONE480_CLANG)
#   define ONE480_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
#   define ONE480_DEPRECATED(msg)
#endif

/* =========================================================
 * İŞ PARÇACIĞI YEREL DEPOLAMA / THREAD-LOCAL STORAGE
 * ========================================================= */

#if defined(ONE480_MSVC)
#   define ONE480_THREAD_LOCAL  __declspec(thread)
#elif defined(ONE480_GCC) || defined(ONE480_CLANG)
#   define ONE480_THREAD_LOCAL  _Thread_local
#else
#   define ONE480_THREAD_LOCAL
#endif

/* =========================================================
 * ERIŞIM HIZALAMA / ALIGNMENT
 * ========================================================= */

#if defined(ONE480_MSVC)
#   define ONE480_ALIGNAS(n)  __declspec(align(n))
#elif defined(ONE480_GCC) || defined(ONE480_CLANG)
#   define ONE480_ALIGNAS(n)  __attribute__((aligned(n)))
#else
#   define ONE480_ALIGNAS(n)
#endif

/* =========================================================
 * YOL SABİTLERİ / PATH CONSTANTS
 * ========================================================= */

/** UTF-8 olarak maksimum yol uzunluğu (Windows uzun yol desteği dahil).
 *  Maximum path length as UTF-8 (including Windows long-path support). */
#define ONE480_PATH_MAX         4096

/** Maksimum dosya adı uzunluğu (uzantı dahil).
 *  Maximum file name length including extension. */
#define ONE480_FILENAME_MAX     260

#ifdef ONE480_WINDOWS
    /** Yol ayırıcı dizesi. / Path separator string. */
#   define ONE480_PATH_SEP      "\\"
    /** Yol ayırıcı karakteri. / Path separator character. */
#   define ONE480_PATH_SEP_CHAR '\\'
#else
#   define ONE480_PATH_SEP      "/"
#   define ONE480_PATH_SEP_CHAR '/'
#endif

/* =========================================================
 * TARAMA İŞ PARÇACIĞI YIĞIT BOYUTU / SCAN THREAD STACK SIZE
 * ========================================================= */

/** Tarama iş parçacıkları için yığıt boyutu (8 MiB).
 *  Stack size for scan worker threads (8 MiB). */
#define ONE480_SCAN_THREAD_STACK_SIZE   (8u * 1024u * 1024u)

/* =========================================================
 * DIZI UZUNLUĞU / ARRAY LENGTH HELPER
 * ========================================================= */

/** Derleme zamanı sabit uzunluklu dizi eleman sayısı.
 *  Compile-time element count of a fixed-length array. */
#define ONE480_ARRLEN(arr)  (sizeof(arr) / sizeof((arr)[0]))

/* =========================================================
 * BÜYÜK-KÜÇÜK ENDIANLIK / ENDIANNESS
 * Not: Bu proje şu an yalnızca little-endian destekler.
 * Note: This project currently supports little-endian only.
 * ========================================================= */

#define ONE480_LITTLE_ENDIAN 1

#endif /* ONE480_PLATFORM_H */
