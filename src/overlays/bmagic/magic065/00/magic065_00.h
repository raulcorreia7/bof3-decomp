#ifndef OVERLAY_BMAGIC_MAGIC065_00_H
#define OVERLAY_BMAGIC_MAGIC065_00_H

/* The bmagic/magic065/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8                  D_801EC2E4;
extern Magic065SharedSteps D_801EEC04;

#define MAGIC065_STEP_COUNT 4

typedef struct Magic065Steps {
    Callback steps[MAGIC065_STEP_COUNT];
} Magic065Steps;

extern Magic065Steps D_801EEC14;

void func_801DE8C0(s32 arg0, s32 arg1, s32 arg2);
void BMagic_SetTextItemName(u8 item_id, u8 category);

#endif
