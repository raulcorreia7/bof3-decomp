#ifndef OVERLAY_BMAGIC_MAGIC083_03_H
#define OVERLAY_BMAGIC_MAGIC083_03_H

/* The bmagic/magic083/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801F0EF0[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0F1C[];
#define BMAGIC_EFFECT_SLOTS D_801F0F1C
#define BMAGIC_EFFECT_COUNT 24
void func_801EFB24(void);
void func_801EF844(void);

#endif
