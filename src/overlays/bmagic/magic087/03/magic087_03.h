#ifndef OVERLAY_BMAGIC_MAGIC087_03_H
#define OVERLAY_BMAGIC_MAGIC087_03_H

/* The bmagic/magic087/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F0540[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F054C[];
#define BMAGIC_EFFECT_SLOTS D_801F054C
#define BMAGIC_EFFECT_COUNT 80
void            func_801EFF50(void);
void            func_801F0014(void);

#endif
