#ifndef OVERLAY_BMAGIC_MAGIC059_03_H
#define OVERLAY_BMAGIC_MAGIC059_03_H

/* The bmagic/magic059/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The amount Effect_CountDownTimer adds to the effect work byte 9. */
#define EFFECT_TIMER_STEP 1

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0694[];
#define BMAGIC_EFFECT_SLOTS D_801F0694
#define BMAGIC_EFFECT_COUNT 24
void func_801EED0C(void);
void func_801EF118(void);
void func_801EFE48(void);

#endif
