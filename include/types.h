#ifndef BASE_TYPES_H
#define BASE_TYPES_H

/* A record asserts its size and each known member offset where it is declared, so a wrong layout fails the build. */

#include <stddef.h>

/*
 * C89-compatible compile-time assertions. The assertion's identifier comes
 * from what it asserts - the type, plus the member for ASSERT_OFFSET - never
 * from __LINE__, so two headers can be included together whatever line their
 * assertions sit on. A name is asserted once per translation unit, and `type`
 * must be one identifier (a typedef name), because it is pasted into it.
 */
#define DECOMP_JOIN_IMPL(a, b)                       a##b
#define DECOMP_JOIN(a, b)                            DECOMP_JOIN_IMPL(a, b)

#define STATIC_ASSERT(name, condition)               typedef char DECOMP_JOIN(static_assertion_, name)[(condition) ? 1 : -1]

#define ASSERT_SIZE(type, expected_size)             STATIC_ASSERT(type, sizeof(type) == (expected_size))

/* PsyQ 3.7's <stddef.h> shadows the compiler's and does not define offsetof. */
#define DECOMP_OFFSETOF(type, member)                ((size_t)&((type*)0)->member)

#define ASSERT_OFFSET(type, member, expected_offset) STATIC_ASSERT(DECOMP_JOIN(type, DECOMP_JOIN(_offset_, member)), DECOMP_OFFSETOF(type, member) == (expected_offset))

/* PsyQ has no boolean type; the game returns flags as an int. C23 and C++ define bool,
 * true and false themselves, so this is only for older C. */
#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L)
enum {
    false,
    true
};

typedef signed int bool;
#endif

/* clang-format off */
typedef signed char        s8;
typedef signed short       s16;
typedef signed int         s32;
typedef signed long long   s64;

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef float              f32;
typedef double             f64;

#endif
