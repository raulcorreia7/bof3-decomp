#ifndef OVERLAY_BMAGIC_MAGIC074_03_H
#define OVERLAY_BMAGIC_MAGIC074_03_H

/* The bmagic/magic074/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;
extern BMagicEffectWork* D_801F20DC;

void func_801F0440(void);

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BMagicEffectWork D_801F055C[];
#define BMAGIC_EFFECT_SLOTS D_801F055C
#define BMAGIC_EFFECT_COUNT 160

#endif
