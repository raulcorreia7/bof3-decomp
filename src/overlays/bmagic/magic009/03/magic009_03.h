#ifndef OVERLAY_BMAGIC_MAGIC009_03_H
#define OVERLAY_BMAGIC_MAGIC009_03_H

/* The bmagic/magic009/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The timer reloads from the second table. */
#define EFFECT_TIMER_RELOAD func_800B0058

/* The amount Effect_CountDownTimer adds to the effect work byte 9. */
#define EFFECT_TIMER_STEP 1

extern BattleHandlerTable5 D_801EEC04;
extern Callback            D_801EF8A4[];

void func_801EF3B8(void);

#endif
