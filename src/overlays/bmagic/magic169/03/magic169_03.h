#ifndef OVERLAY_BMAGIC_MAGIC169_03_H
#define OVERLAY_BMAGIC_MAGIC169_03_H

/* The bmagic/magic169/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s16                 D_1F800004;
extern BMagicEffectFuncs   D_801EEC14;
extern Magic010SharedSteps D_801EEC04;
void                       func_800AF764(void);
void                       func_801EF070(void);
void                       func_801EF860(void);
extern Callback            D_801F0420[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect        D_801F0424[];
#define BMAGIC_EFFECT_SLOTS D_801F0424
#define BMAGIC_EFFECT_COUNT 80


#endif
