#ifndef OVERLAY_BMAGIC_MAGIC219_03_H
#define OVERLAY_BMAGIC_MAGIC219_03_H

/* The bmagic/magic219/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern Callback     D_801EFA04[];
extern BattleEffect D_801EFA14[];
#define BMAGIC_EFFECT_SLOTS D_801EFA14
#define BMAGIC_EFFECT_COUNT 32
/* func_801EF024 */
void BMagic_DispatchEffectMode(void);

#define MAGIC219_STEP_COUNT 4

typedef struct Magic219Steps {
    Callback steps[MAGIC219_STEP_COUNT];
} Magic219Steps;

extern Magic219Steps D_801EEC04;

#endif
