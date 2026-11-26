#ifndef SYSTEM_SCHED_H
#define SYSTEM_SCHED_H

#include "common/callback.h"
#include "psx/mem.h"
#include "types.h"

#define SYS_THREAD_FORCE_SWITCH ((s32)0xff000000u)

/* SYS_ThreadRegister scales the slot index with
 * `sll $a0, $a0, 7` and then stores the state halfword at slot+0x00
 * (`sh $v0, %lo(D_80143B40)($at)`, value 2 = SYS_THREAD_OPEN) and the
 * entry word at +0x04 (`sw $a1, %lo(D_80143B44)($at)`). */
#define SYS_THREAD_SIZE         0x80
#define SYS_THREAD_COUNT        4

/* The scheduler: 0x80-byte thread records, a cursor, and the entry points that register, run and stop threads. */

/* retail addresses */

/* The thread state SYS_ThreadRun switches on. */
typedef enum ThreadState {
    SYS_THREAD_EMPTY     = 0,
    SYS_THREAD_YIELD     = 1,
    SYS_THREAD_OPEN      = 2,
    SYS_THREAD_SWITCH    = 4,
    SYS_THREAD_SUSPENDED = 0x40,
    SYS_THREAD_IDLE      = 0x7f,
} ThreadState;

/* The bytes SYS_ClearCurrentThread clears before a registered entry runs: eight halfwords ending at
 * 0x18 + 0xE and the 16-byte run at 0x28 of the work area. */
typedef struct ThreadClear {
    u8             pad_00[0x18];
    /* 0x18 */ u16 halfword[8];
    /* 0x28 */ u8  byte[0x10];
} ThreadClear;

ASSERT_OFFSET(ThreadClear, halfword, 0x18);
ASSERT_OFFSET(ThreadClear, byte, 0x28);
ASSERT_SIZE(ThreadClear, 0x38);

/* Thread slot 0: the game entry state machine the field update leaves for the next frame. */
typedef struct ThreadGameEntry {
    u8             pad_00[0x08];
    /* 0x08 */ u16 state; /* GameMode */
    /* 0x0A */ u16 substate;
    u8             pad_0C[0x1C];
    /* 0x28 */ u8  request; /* GameRequest */
    u8             pad_29[0x0F];
} ThreadGameEntry;

ASSERT_OFFSET(ThreadGameEntry, state, 0x08);
ASSERT_OFFSET(ThreadGameEntry, substate, 0x0A);
ASSERT_OFFSET(ThreadGameEntry, request, 0x28);
ASSERT_SIZE(ThreadGameEntry, 0x38);

/* Thread slot 1: the title screen's fade, banner and choice state. The popup
 * request word holds the pending flag in its low byte and the three phase
 * bytes above it. */
typedef struct ThreadTitleScreen {
    u8             pad_00[0x08];
    /* 0x08 */ u16 state;
    /* 0x0A */ u16 substate;
    u8             pad_0C[0x0C];
    /* 0x18 */ s16 timer;
    /* 0x1A */ s16 banner_scroll;
    /* 0x1C */ s16 banner_alpha;
    /* 0x1E */ u16 primary_alpha;
    /* 0x20 */ u16 secondary_alpha;
    /* 0x22 */ u16 pulse;
    u8             pad_24[0x04];

    union {
        /* 0x28 */ u32 request; /* WIN_POPUP_* flags, tested through the low byte */
        struct {
            /* 0x28 */ u8 pending;
            /* 0x29 */ u8 fade_phase;
            /* 0x2A */ u8 choice_phase;
            /* 0x2B */ u8 input_gate;
        } bytes;
    } popup;

    u8 pad_2C[0x0C];
} ThreadTitleScreen;

ASSERT_OFFSET(ThreadTitleScreen, timer, 0x18);
ASSERT_OFFSET(ThreadTitleScreen, pulse, 0x22);
ASSERT_OFFSET(ThreadTitleScreen, popup, 0x28);
ASSERT_OFFSET(ThreadTitleScreen, pad_2C, 0x2C);
ASSERT_SIZE(ThreadTitleScreen, 0x38);

/* Thread slot 2: the window effect's local mode; Thread.state is its busy flag. */
typedef struct ThreadScreenEffect {
    u8             pad_00[0x08];
    /* 0x08 */ u16 mode; /* UiMode */
    u8             pad_0A[0x2E];
} ThreadScreenEffect;

ASSERT_OFFSET(ThreadScreenEffect, mode, 0x08);
ASSERT_SIZE(ThreadScreenEffect, 0x38);

/* The 0x38-byte work area each thread slot overlays with the record of the entry SYS_ThreadRegister armed for it. */
typedef union ThreadTail {
    ThreadClear        clear;
    ThreadGameEntry    game_entry;
    ThreadTitleScreen  title_screen;
    ThreadScreenEffect screen_effect;
} ThreadTail;

ASSERT_SIZE(ThreadTail, 0x38);

typedef struct Thread {
    u16        state; /* ThreadState */
    u16        countdown;
    Callback   entry;
    s32        thread_id;
    u8*        work;  /* 0x0C - the kernel work block whose +0x94 word this thread's context keeps */
    u32        stack; /* thread stack top, OpenTh's sp argument */
    u8         pad_14[0x30];
    u32        gp;   /* OpenTh's gp argument */
    ThreadTail tail; /* the armed entry's own state, cleared by SYS_ClearCurrentThread */
} Thread;

ASSERT_OFFSET(Thread, state, 0x00);
ASSERT_OFFSET(Thread, entry, 0x04);
ASSERT_OFFSET(Thread, work, 0x0C);
ASSERT_OFFSET(Thread, stack, 0x10);
ASSERT_OFFSET(Thread, gp, 0x44);
ASSERT_OFFSET(Thread, tail, 0x48);
ASSERT_SIZE(Thread, SYS_THREAD_SIZE);

/* D_80143B40 */
extern Thread g_SysThreads[]; /* four threads, 0x80 bytes each */

#endif
