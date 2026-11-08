#ifndef OVERLAY_BMAGIC_MAGIC057_03_H
#define OVERLAY_BMAGIC_MAGIC057_03_H

/* The bmagic/magic057/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleEffect* volatile D_801EC2E0;

typedef struct Magic057Steps801EEC10 {
    Callback steps[4];
} Magic057Steps801EEC10;

typedef struct Magic057Steps801EEC20 {
    Callback steps[3];
} Magic057Steps801EEC20;

extern Magic057Steps801EEC10 D_801EEC10;
extern Magic057Steps801EEC20 D_801EEC20;

extern Magic057Steps801EEC20 D_801EEC2C;

extern Magic057Steps801EEC20 D_801EEC38;

extern Magic057Steps801EEC20 D_801EEC44;

extern u8 D_801EFADC[];
#endif
