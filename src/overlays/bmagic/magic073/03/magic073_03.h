#ifndef OVERLAY_BMAGIC_MAGIC073_03_H
#define OVERLAY_BMAGIC_MAGIC073_03_H

/* The bmagic/magic073/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;
extern BMagicEffectWork* D_801F21F0;

void func_801F0454(void);

u8 func_801F04A4(void);

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BMagicEffectWork D_801F0670[];
#define BMAGIC_EFFECT_SLOTS D_801F0670
#define BMAGIC_EFFECT_COUNT 160

#endif
