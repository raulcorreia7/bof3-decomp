#ifndef OVERLAY_BMAGIC_MAGIC017_03_H
#define OVERLAY_BMAGIC_MAGIC017_03_H

/* The bmagic/magic017/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC017_STEP_COUNT 10

typedef struct Magic017Steps {
    Callback handlers[MAGIC017_STEP_COUNT];
} Magic017Steps;

extern Magic017Steps D_801EEC10;

/* The battle/battle/15 sprite-cell routines, called with a battler or the effect work record. */
u32  func_800AFB48(PartyMember* record);
void func_800AF8F0(PartyMember* record);

#endif
