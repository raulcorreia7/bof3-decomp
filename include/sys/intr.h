#ifndef SYS_INTR_H
#define SYS_INTR_H

#include "types.h"
#include "common/callback.h"

/* The interrupt-callback pair SetPatchPad enqueues (SLUS_004.22 and LOGO.EXE): two callback slots and the trailing word it clears. */
typedef Callback InterruptCallbacks[2];

typedef struct InterruptHooks {
    InterruptCallbacks callbacks;
    s32                pad; /* cleared when SetPatchPad queues the pair, never read by game code */
} InterruptHooks;

ASSERT_SIZE(InterruptHooks, 0x0C);

/* The dispatch table behind D_80185690. */
typedef struct IntrDispatch {
    u32 unk_00;
    s32 (*unk_04)();
    s32 (*unk_08)();
    s32 (*unk_0C)();
    s32 (*unk_10)();
    s32 (*unk_14)();
} IntrDispatch;

#endif
