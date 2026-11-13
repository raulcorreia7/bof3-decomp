#ifndef OVERLAY_BMAGIC_MAGIC001_00_H
#define OVERLAY_BMAGIC_MAGIC001_00_H

/* The bmagic/magic001/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC001_STEP_COUNT 11

typedef struct Magic001Steps {
    Callback handlers[MAGIC001_STEP_COUNT];
} Magic001Steps;

#define MAGIC001_SECOND_STEP_COUNT 3

typedef struct Magic001SecondSteps {
    Callback steps[MAGIC001_SECOND_STEP_COUNT];
} Magic001SecondSteps;

extern Magic001Steps       D_801EEC10;
extern Magic001SecondSteps D_801EEC3C;
extern Callback            D_801EEC48[];

void func_801F0238(void);

extern SVECTOR D_1F800014[];

static inline void BMagic_ClearWorkFlagsAndStep(void) {
    if (g_Task->param.unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        g_Task->header.mode += 1;
    }
}

#endif
