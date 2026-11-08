#ifndef OVERLAY_BMAGIC_MAGIC017_03_H
#define OVERLAY_BMAGIC_MAGIC017_03_H

/* The bmagic/magic017/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC017_STEP_COUNT 8

typedef struct Magic017Steps {
    Callback steps[MAGIC017_STEP_COUNT];
} Magic017Steps;

extern Magic017Steps D_801EEC10;
extern u8            g_BattleActiveBattler;

#endif
