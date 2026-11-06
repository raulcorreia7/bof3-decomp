#ifndef SYS_INTR_H
#define SYS_INTR_H

#include "types.h"
#include "common/handler.h"

/* The interrupt-handler pair behind D_8018DB44 (SLUS_004.22) and D_801EB654
 * (LOGO.EXE): two handler slots and the trailing word. */
typedef struct InterruptHooks {
    s32 (*handler1)(void);
    s32 (*handler2)(void);
    s32 pad;
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
