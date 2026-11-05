#ifndef OVERLAY_BMAGIC_MAGIC105_03_H
#define OVERLAY_BMAGIC_MAGIC105_03_H

/* The bmagic/magic105/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern MagicTaskFuncs D_801EEC04;
/* The step handlers the bank-swap runner dispatches. */
extern Callback     D_801F0078[];

void func_800AF764(void);
/* The x/y speed pairs the step indexes by the work counter. */
extern s16 D_801F004C[];
extern s16 D_801F004E[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect   D_801F00A0[];
#define BMAGIC_EFFECT_SLOTS D_801F00A0
#define BMAGIC_EFFECT_COUNT 64

#endif
