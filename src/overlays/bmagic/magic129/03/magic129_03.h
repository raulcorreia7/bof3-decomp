#ifndef OVERLAY_BMAGIC_MAGIC129_03_H
#define OVERLAY_BMAGIC_MAGIC129_03_H

/* The bmagic/magic129/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern Callback     D_801F05B8[];
extern BattleEffect D_801F05D8[];
#define BMAGIC_EFFECT_SLOTS D_801F05D8
#define BMAGIC_EFFECT_COUNT 64
void func_801EFF40(void);

typedef struct Magic129Steps {
    Callback steps[3];
} Magic129Steps;

extern Magic129Steps D_801EEC04;

#endif
