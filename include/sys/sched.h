#ifndef SYSTEM_SCHED_H
#define SYSTEM_SCHED_H

#include "common/handler.h"
#include "psx/mem.h"
#include "types.h"

#define CALLBACK_FORCE_SWITCH ((s32)0xff000000u)

/* func_8014B854 (CbRegister) scales the slot index with
 * `sll $a0, $a0, 7` and then stores the state halfword at slot+0x00
 * (`sh $v0, %lo(D_80143B40)($at)`, value 2 = CALLBACK_SLOT_OPEN) and the
 * callback word at slot+0x04 (`sw $a1, %lo(D_80143B44)($at)`). */
#define CALLBACK_SLOT_SIZE    0x80

/* The callback scheduler: 0x80-byte slots, a cursor, and the entry points that
 * register, count, and run callbacks. */

/* retail addresses */

/* The slot state func_8014B73C switches on: EMPTY and YIELD after a callback
 * returns, OPEN when CbRegister arms a slot, SWITCH for the forced switch, and
 * IDLE when the scheduler parks. */
typedef enum CallbackSlotState {
    CALLBACK_SLOT_EMPTY  = 0,
    CALLBACK_SLOT_YIELD  = 1,
    CALLBACK_SLOT_OPEN   = 2,
    CALLBACK_SLOT_SWITCH = 4,
    CALLBACK_SLOT_IDLE   = 0x7f,
} CallbackSlotState;

typedef struct CallbackSlot {
    u16      state; /* CallbackSlotState */
    u16      countdown;
    Callback callback;
    s32      thread_id;
    u32      unk_0C;
    u32      open_arg;
    u8       pad_14[0x30];
    u32      open_arg_2;
    u8       pad_48[0x38];
} CallbackSlot;

ASSERT_SIZE(CallbackSlot, CALLBACK_SLOT_SIZE);
ASSERT_OFFSET(CallbackSlot, state, 0x00);
ASSERT_OFFSET(CallbackSlot, callback, 0x04);

/* func_8014AEE0 */
void SYS_RunLogo(void);
/* func_8014AFC0 */
void SYS_UpdateKeyState(void);
/* func_8014B020 */
void SYS_PrepareFrame(void);
/* func_8014B0F0 */
void SYS_SubmitFrame(void);
/* func_8014B17C */
void SYS_CaptureDrawTime(void);
/* func_8014B33C */
void CallbackStopAll(void);
/* func_8014B6B4 */
void CallbackInitThreads(void);
/* func_8014B73C */
void CallbackRun(void);
/* func_8014B854 */
void CallbackRegister(s32 callback_slot, Callback callback);
/* func_8014B87C */
void CallbackWait(u16 countdown);
/* func_8014B8B0 */
void CallbackExit(void);
/* func_8014B900 */
void CallbackCloseThread(s32 callback_slot);

#endif
