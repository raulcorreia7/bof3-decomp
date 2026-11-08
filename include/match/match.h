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
 * Matching vocabulary for lifted C89.
 *
 * Prefer idiomatic C that naturally matches. Reach for MATCH_* only when
 * compiler behavior prevents a clean match. Annotate every use: a matching
 * fake-match helper gets an adjacent `FAKE:` note; an original-game bug keeps a
 * nearby comment that says so.
 *
 * Fake-match helpers, in escalating order:
 *   1. correct types and signedness (types.h);
 *   2. recover original control-flow/source shape;
 *   3. adjust temporary lifetimes and declaration order;
 *   4. correct casts and expression grouping;
 *   5. match compiler/version/flags per translation unit (build description);
 *   6. MATCH_VOLATILE when it affects required codegen;
 *   7. MATCH_BARRIER to constrain scheduling/reloads;
 *   8. MATCH_REG to pin an allocator;
 *   9. inline ASM as the final escape hatch.
 *
 * The whole vocabulary is gated by MATCHING: defined in the canonical matching
 * build, so fake-match helpers are live while matching and become inert in a
 * build that omits it.
 */

/*
 * Prevent sibling-call optimization when the original binary contains
 * a real call instruction rather than a tail call.
 */
#if defined(MATCHING)
#define NO_SIBLING_CALLS                __attribute__((optimize("no-optimize-sibling-calls")))

/*
 * Canonical fake-match-helper spellings, `MATCH_FAKE_*`. One family for the two
 * verified fake-match helper shapes:
 *
 *   MATCH_FAKE_BARRIER()            barrier   (same constraint as MATCH_BARRIER)
 *   MATCH_FAKE_PIN(type, name, reg) register  (same constraint as MATCH_REG)
 *
 * Each expands to the constraint of the macro it mirrors, so a converted site
 * is byte-identical to the expanded spelling it replaces, and the expanded
 * compiler-constraint spellings stay permitted. Keep the adjacent
 * `/* FAKE: <reason> *\/` note and the `fakes:` landing line, and count the
 * expanded spelling as a helper.
 *
 * The barrier and pin are distinct fixed-arity macros rather than one
 * polymorphic name because the period preprocessor neither expands variadic
 * macros nor re-expands a pasted function-like name, so no single name can
 * select both shapes there.
 */
#define MATCH_FAKE_BARRIER()            __asm__ __volatile__("" : : : "memory")
#define MATCH_FAKE_PIN(type, name, reg) register type name asm(reg)

#define MATCH_BARRIER()                 __asm__ __volatile__("" : : : "memory")

/*
 * Last-resort local allocator constraint. After the clean-C ladder and
 * a search over source rewrites, use once only for an allocator or entry-register
 * residual that the disassembly diff shows; retain only with an independent review and a live exact match.
 * Direct numeric pins still need explicit user approval. reg is a GCC MIPS
 * name.
 */
#define MATCH_REG(type, name, reg)      register type name asm(reg)
/*
 * The macro form is supported by the current PsyQ compiler for ordinary
 * allocator pins. Legacy pins using numeric "$N" register spellings remain
 * direct declarations until their compiler syntax is separately verified.
 */

/* Force a local to a volatile object when codegen depends on the store/load. */
#define MATCH_VOLATILE(type, name)      volatile type name

/* Force one access to go through a volatile pointer when codegen depends on
 * the reload, without declaring a volatile object or local. */
#define MATCH_VOLATILE_PTR(type, expr)  (volatile type*)(expr)

/* Harmful: register-level operand constraints. MATCH_FAKE_OPAQUE hides x's value
 * from the optimizer (it may have changed), so the compiler keeps x in a
 * register; MATCH_FAKE_USE forces x live in a register at this point. */
#define MATCH_FAKE_OPAQUE(x)            __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define MATCH_FAKE_USE(x)               __asm__ __volatile__("" : : "r"(x))

#else
#define NO_SIBLING_CALLS
#define MATCH_FAKE_BARRIER()
#define MATCH_FAKE_PIN(type, name, reg) type name
#define MATCH_BARRIER()
#define MATCH_REG(type, name, reg)     type name
#define MATCH_VOLATILE(type, name)     type name
#define MATCH_VOLATILE_PTR(type, expr) (type*)(expr)
#define MATCH_FAKE_OPAQUE(x)
#define MATCH_FAKE_USE(x)
#endif

/* Retail frame bytes that no statement, struct, array, spilled argument or
 * local type explains: n unused objects of type, declared the same in every mode
 * (the size only matters when matching). A declaration:
 * place it with the other locals at block start. */
#define STACK_PADS(type, n)          type stack_pad[n]

/* A local holds a constant so the loop pass hoists it in retail order. A
 * declaration, the same in every mode: `s32 MATCH_FAKE_HOLD(x, 4);`. Needs an
 * adjacent FAKE: note with the evidence (best pure-C match %, the rewrites tried). */
#define MATCH_FAKE_HOLD(name, value) name = (value)

/* Volatile access to an existing object. */
#define VOL(type, x)                 (*(volatile type*)&(x))

/*
 * Register-clobber barriers for MIPS delay-slot ordering.
 *
 * These constrain caller-register scheduling for a C-generated instruction,
 * including jal/branch delay-slot placement and fixed-address reload ordering.
 * They do not emit or select an opcode; use them only after the disassembly diff
 * shows the required register and placement.
 */
#if defined(__GNUC__) && defined(MATCHING)
/* One shorthand macro per caller-saved register. */
#define CLOBBER_A0() __asm__ __volatile__("" : : : "a0")
#define CLOBBER_A1() __asm__ __volatile__("" : : : "a1")
#define CLOBBER_A2() __asm__ __volatile__("" : : : "a2")
#define CLOBBER_A3() __asm__ __volatile__("" : : : "a3")
#define CLOBBER_V0() __asm__ __volatile__("" : : : "v0")
#define CLOBBER_V1() __asm__ __volatile__("" : : : "v1")
#define CLOBBER_T0() __asm__ __volatile__("" : : : "t0")
#define CLOBBER_T1() __asm__ __volatile__("" : : : "t1")
#define CLOBBER_T2() __asm__ __volatile__("" : : : "t2")
#define CLOBBER_T3() __asm__ __volatile__("" : : : "t3")
#define CLOBBER_T4() __asm__ __volatile__("" : : : "t4")
#define CLOBBER_T5() __asm__ __volatile__("" : : : "t5")
#define CLOBBER_T6() __asm__ __volatile__("" : : : "t6")
#define CLOBBER_T7() __asm__ __volatile__("" : : : "t7")
#define CLOBBER_T8() __asm__ __volatile__("" : : : "t8")
#define CLOBBER_T9() __asm__ __volatile__("" : : : "t9")
#else
#define CLOBBER_A0()
#define CLOBBER_A1()
#define CLOBBER_A2()
#define CLOBBER_A3()
#define CLOBBER_V0()
#define CLOBBER_V1()
#define CLOBBER_T0()
#define CLOBBER_T1()
#define CLOBBER_T2()
#define CLOBBER_T3()
#define CLOBBER_T4()
#define CLOBBER_T5()
#define CLOBBER_T6()
#define CLOBBER_T7()
#define CLOBBER_T8()
#define CLOBBER_T9()
#endif

/*
 * Basic-block boundary that holds one statement in place in the instruction
 * schedule. Use ONLY when the byte diff proves the scheduler reorders that
 * statement against a neighbor without it. Pure textual expansion, identical
 * to the literal do/while spelling; every use must still pass the byte check.
 */
#if defined(MATCHING)
#define ORDER_LOCK(stmt) \
    do {                 \
        stmt;            \
    } while (0)
#else
#define ORDER_LOCK(stmt) stmt
#endif

/*
 * The same boundary around a run of statements. Write ORDER_LOCK_BEGIN on its
 * own line and close it with `ORDER_LOCK_END;`. The pair opens and closes one
 * block, so it must sit inside a single block of its own. Moving statements
 * into or out of the pair moves the boundary; byte-check every change.
 */
#if defined(MATCHING)
#define ORDER_LOCK_BEGIN do {
#define ORDER_LOCK_END \
    }                  \
    while (0)
#else
#define ORDER_LOCK_BEGIN {
#define ORDER_LOCK_END   }
#endif

/*
 * An empty boundary: splits the schedule at this point without holding any
 * statement. Same rules as ORDER_LOCK.
 */
#if defined(MATCHING)
#define ORDER_FENCE() \
    do {              \
    } while (0)
#else
#define ORDER_FENCE() ((void)0)
#endif

/*
 * Unmatched code/data inclusion for C source. The assembler-side set for the
 * split path lives in `include/match/include_asm.h`; this header is the one
 * game source sees. `ASM_DIR` is the image's one asm folder, passed as
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
 * Marker macros for intentionally-unmatched or non-equivalent code, and
 * function bodies that live entirely in assembly. They expand to nothing and
 * tag the construct for readers and the build.
 *
 * Status rule: every lifted function carries exactly one status marker
 * inline at the start of its own definition line (`MATCH void func_...`,
 * `NON_MATCHING void func_...`), so tree state is greppable. MATCH marks a
 * compiled definition; NON_MATCHING marks a draft under `#ifdef NON_MATCHING`
 * whose `#else` links the split assembly. No definition is exempt: a PsyQ stub such as
 * `__main` carries MATCH, and only a `static inline` helper in a header goes without.
 * `INCLUDE_ASM` lines take no marker. `tools/check_markers.py` enforces the rule.
 *
 * The draft build passes `-DNON_MATCHING`; the marker then expands to nothing so
 * the draft definition compiles. Without the flag the branch is skipped, which
 * keeps the INCLUDE_ASM fallback as the build path.
 */
#ifndef MATCH
#define MATCH
#endif

#ifdef NON_MATCHING
#undef NON_MATCHING
#define NON_MATCHING
#endif

#endif /* BASE_MATCH_H */
