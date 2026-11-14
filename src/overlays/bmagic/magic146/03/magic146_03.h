#ifndef OVERLAY_BMAGIC_MAGIC146_03_H
#define OVERLAY_BMAGIC_MAGIC146_03_H

/* The bmagic/magic146/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801EF9B8[];
extern Callback     D_801EF9C0[];
extern Callback     D_801EF9C4[];
extern Point3l     D_801EF9D0[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EF9F4[];
#define BMAGIC_EFFECT_SLOTS D_801EF9F4
#define BMAGIC_EFFECT_COUNT 64

void func_801EF2FC(void);

#define MAGIC146_STEP_COUNT 3

typedef struct Magic146Steps {
    Callback steps[MAGIC146_STEP_COUNT];
} Magic146Steps;

extern Magic146Steps D_801EEC04;

#endif
