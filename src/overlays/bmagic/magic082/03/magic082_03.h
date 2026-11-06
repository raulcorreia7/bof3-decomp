#ifndef OVERLAY_BMAGIC_MAGIC082_03_H
#define OVERLAY_BMAGIC_MAGIC082_03_H

/* The bmagic/magic082/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect ticker value below which Effect_NextStep advances the step. */
#define EFFECT_STEP_LIMIT 2

extern BmagicEffectFuncs D_801EEC04;

extern Callback D_801F0D1C[];
void            func_801EF720(void);
void            func_801EFA00(void);

void func_801F03E0(void);

#endif
