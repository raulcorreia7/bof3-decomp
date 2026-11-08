#ifndef OVERLAY_BMAGIC_MAGIC065_00_H
#define OVERLAY_BMAGIC_MAGIC065_00_H

/* The bmagic/magic065/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8                D_801EC2E4;
extern Func801EEC24Steps D_801EEC04;

typedef struct Magic065Steps {
    Callback steps[4];
} Magic065Steps;

extern Magic065Steps D_801EEC14;

void func_801DE8C0(s32 arg0, s32 arg1, s32 arg2);
void BMagic_SetTextItemName(u8 item_id, u8 category);

#endif
