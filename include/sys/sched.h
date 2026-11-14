#ifndef SYSTEM_SCHED_H
#define SYSTEM_SCHED_H

#include "common/handler.h"
#include "psx/mem.h"
#include "types.h"

#define SYS_THREAD_FORCE_SWITCH ((s32)0xff000000u)

/* func_8014B854 (CbRegister) scales the slot index with
 * `sll $a0, $a0, 7` and then stores the state halfword at slot+0x00
 * (`sh $v0, %lo(D_80143B40)($at)`, value 2 = CALLBACK_SLOT_OPEN) and the
 * callback word at slot+0x04 (`sw $a1, %lo(D_80143B44)($at)`). */
#define SYS_THREAD_SIZE         0x80

/* The callback scheduler: 0x80-byte slots, a cursor, and the entry points that
 * register, count, and run callbacks. */

/* retail addresses */

/* The slot state func_8014B73C switches on: EMPTY and YIELD after a callback
 * returns, OPEN when CbRegister arms a slot, SWITCH for the forced switch, and
 * IDLE when the scheduler parks. */
typedef enum ThreadState {
    CALLBACK_SLOT_EMPTY = 0,
    CALLBACK_SLOT_YIELD = 1,
    CALLBACK_SLOT_OPEN  = 2,
    SYS_THREAD_SWITCH   = 4,
    SYS_THREAD_IDLE     = 0x7f,
} ThreadState;

typedef struct Thread {
    u16      state; /* ThreadState */
    u16      countdown;
    Callback callback;
    s32      thread_id;
    u32      unk_0C;
    u32      open_arg;
    u8       pad_14[0x30];
    u32      open_arg_2;
    u8       pad_48[0x38];
} Thread;

ASSERT_SIZE(Thread, SYS_THREAD_SIZE);
ASSERT_OFFSET(Thread, state, 0x00);
ASSERT_OFFSET(Thread, callback, 0x04);

#endif
