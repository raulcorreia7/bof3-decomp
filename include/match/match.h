#ifndef BASE_MATCH_H
#define BASE_MATCH_H

#include "types.h"

/*
 * Assembly-match switch for asm-authored originals (hand-written or an
 * inline-asm macro): the bytes were authored in assembly, not emitted by the
 * compiler. Default 1: the included, byte-exact assembly is the build path.
 * Set -DBOF3_ASM_MATCH=0 to compile the file's INFERRED C semantic model
 * instead (documentation note; NOT byte-checked). A build without MATCHING
 * always uses the model.
 */
#ifndef BOF3_ASM_MATCH
#define BOF3_ASM_MATCH 1
#endif
#if BOF3_ASM_MATCH && defined(MATCHING)
#define BOF3_USE_ASM 1
#else
#define BOF3_USE_ASM 0
#endif

/*
 * Fake-match helpers, `FAKE_*`. Prefer idiomatic C that naturally matches;
 * reach for a helper only when compiler behavior prevents a clean match. Every
 * use gets an adjacent `FAKE:` note with the reason and the best pure-C score.
 * An original-game bug keeps a nearby comment that says so.
 *
 * In escalating order:
 *   1. correct types and signedness (types.h);
 *   2. recover original control-flow/source shape;
 *   3. adjust temporary lifetimes and declaration order;
 *   4. correct casts and expression grouping;
 *   5. match compiler/version/flags per translation unit (build description);
 *   6. FAKE_VOLATILE_PTR when it affects required codegen;
 *   7. FAKE_BARRIER, FAKE_ORDER_*, FAKE_STACK_PADS, FAKE_HOLD;
 *   8. FAKE_REG, FAKE_OPAQUE, FAKE_USE, FAKE_CLOBBER_*;
 *   9. inline ASM as the final escape hatch.
 *
 * The whole vocabulary is gated by MATCHING: live in the canonical matching
 * build, inert in a build that omits it. These are not status markers; see
 * the status markers (`MATCH`, `NON_MATCHING`) below.
 */
#if defined(MATCHING)
/* Barrier that constrains scheduling and reloads. */
#define FAKE_BARRIER()                __asm__ __volatile__("" : : : "memory")

/*
 * Last-resort local allocator constraint. After the clean-C ladder and
 * a search over source rewrites, use once only for an allocator or entry-register
 * residual that the disassembly diff shows; retain only with an independent review and a live exact match.
 * Direct numeric pins still need explicit user approval. reg is a GCC MIPS
 * name. Legacy pins using numeric "$N" register spellings remain direct
 * declarations until their compiler syntax is separately verified.
 */
#define FAKE_REG(type, name, reg)     register type name asm(reg)

/* Force one access to go through a volatile pointer when codegen depends on
 * the reload, without declaring a volatile object or local. */
#define FAKE_VOLATILE_PTR(type, expr) (volatile type*)(expr)

/* Register-level operand constraints. FAKE_OPAQUE hides x's value from the
 * optimizer (it may have changed), so the compiler keeps x in a register;
 * FAKE_USE forces x live in a register at this point. */
#define FAKE_OPAQUE(x)                __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define FAKE_USE(x)                   __asm__ __volatile__("" : : "r"(x))

#else
#define FAKE_BARRIER()
#define FAKE_REG(type, name, reg)     type name
#define FAKE_VOLATILE_PTR(type, expr) (type*)(expr)
#define FAKE_OPAQUE(x)
#define FAKE_USE(x)
#endif

/* Retail frame bytes that no statement, struct, array, spilled argument or
 * local type explains: n unused objects of type, declared the same in every mode
 * (the size only matters when matching). A declaration:
 * place it with the other locals at block start. */
#define FAKE_STACK_PADS(type, n) type stack_pad[n]

/* A local holds a constant so the loop pass hoists it in retail order. A
 * declaration, the same in every mode: `s32 FAKE_HOLD(x, 4);`. Needs an
 * adjacent FAKE: note with the best pure-C match % and the rewrites tried. */
#define FAKE_HOLD(name, value)   name = (value)

/* Volatile access to an existing object. */
#define VOL(type, x)             (*(volatile type*)&(x))

/*
 * Register-clobber barriers for MIPS delay-slot ordering.
 *
 * These constrain caller-register scheduling for a C-generated instruction,
 * including jal/branch delay-slot placement and fixed-address reload ordering.
 * They do not emit or select an opcode; use them only after the disassembly diff
 * shows the required register and placement. One macro per register in use.
 */
#if defined(__GNUC__) && defined(MATCHING)
#define FAKE_CLOBBER_A1() __asm__ __volatile__("" : : : "a1")
#define FAKE_CLOBBER_A2() __asm__ __volatile__("" : : : "a2")
#define FAKE_CLOBBER_A3() __asm__ __volatile__("" : : : "a3")
#else
#define FAKE_CLOBBER_A1()
#define FAKE_CLOBBER_A2()
#define FAKE_CLOBBER_A3()
#endif

/*
 * Basic-block boundary that holds one statement in place in the instruction
 * schedule. Use ONLY when the byte diff proves the scheduler reorders that
 * statement against a neighbor without it. Pure textual expansion, identical
 * to the literal do/while spelling; every use must still pass the byte check.
 */
#if defined(MATCHING)
#define FAKE_ORDER_LOCK(stmt) \
    do {                      \
        stmt;                 \
    } while (0)
#else
#define FAKE_ORDER_LOCK(stmt) stmt
#endif

/*
 * The same boundary around a run of statements. Write FAKE_ORDER_LOCK_BEGIN on its
 * own line and close it with `FAKE_ORDER_LOCK_END;`. The pair opens and closes one
 * block, so it must sit inside a single block of its own. Moving statements
 * into or out of the pair moves the boundary; byte-check every change.
 */
#if defined(MATCHING)
#define FAKE_ORDER_LOCK_BEGIN do {
#define FAKE_ORDER_LOCK_END \
    }                       \
    while (0)
#else
#define FAKE_ORDER_LOCK_BEGIN {
#define FAKE_ORDER_LOCK_END   }
#endif

/*
 * An empty boundary: splits the schedule at this point without holding any
 * statement. Same rules as FAKE_ORDER_LOCK.
 */
#if defined(MATCHING)
#define FAKE_ORDER_FENCE() \
    do {                   \
    } while (0)
#else
#define FAKE_ORDER_FENCE() ((void)0)
#endif

/*
 * Unmatched code/data inclusion for C source. `ASM_DIR` is the image's one asm folder, passed as
 * `-DASM_DIR="asm/<target>"` (or its `hand` subfolder for authored assembly).
 */
#if defined(MATCHING) && !defined(M2CTX) && !defined(PERMUTER)
#ifndef ASM_DIR
#error "INCLUDE_ASM needs -DASM_DIR=\"asm/<target>\" from the build"
#endif
#ifndef INCLUDE_ASM
#define INCLUDE_ASM(NAME)                                \
    __asm__(".section .text\n"                           \
            "    .set noat\n"                            \
            "    .set noreorder\n"                       \
            "    .include \"" ASM_DIR "/" #NAME ".s\"\n" \
            "    .set reorder\n"                         \
            "    .set at\n")
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(NAME)                             \
    __asm__(".section .rodata\n"                         \
            "    .include \"" ASM_DIR "/" #NAME ".s\"\n" \
            ".section .text")
#endif
#else
#ifndef INCLUDE_ASM
#define INCLUDE_ASM(NAME)
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(NAME)
#endif
#endif

/*
 * Status markers. They expand to nothing and tag the construct for readers and
 * the build; they are not FAKE_* helpers and never need a `FAKE:` note.
 *
 *   MATCH         this C is the original: it compiles to the retail bytes.
 *   NON_MATCHING  a C draft under `#ifdef NON_MATCHING`; the split assembly in
 *                 the `#else` builds until the draft matches.
 *   HAND_ASM      the original was hand-written assembly; this C, under
 *                 `#ifdef NON_MATCHING`, is its equivalent (same inputs, outputs
 *                 and effects) and the `#else` assembly stays the build path.
 *                 Every function in `asm/<target>/hand/` has one. It counts
 *                 separately from C matches and is not debt.
 *
 * Every lifted function carries exactly one status marker inline at the start
 * of its own definition line (`MATCH void func_...`), so tree state is
 * greppable. No definition is exempt: a PsyQ stub such as `__main` carries
 * MATCH, and only a `static inline` helper in a header goes without.
 * `INCLUDE_ASM` lines take no marker. `tools/check_markers.py` enforces the rule.
 *
 * The draft build passes `-DNON_MATCHING`; the markers then expand to nothing
 * so the draft definition compiles. Without the flag the branch is skipped,
 * which keeps the INCLUDE_ASM as the build path.
 */
#ifndef MATCH
#define MATCH
#endif

#ifndef HAND_ASM
#define HAND_ASM
#endif

#ifdef NON_MATCHING
#undef NON_MATCHING
#define NON_MATCHING
#endif

#endif /* BASE_MATCH_H */
