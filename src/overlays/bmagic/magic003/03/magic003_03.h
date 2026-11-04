#ifndef OVERLAY_BMAGIC_MAGIC003_03_H
#define OVERLAY_BMAGIC_MAGIC003_03_H

/* The bmagic/magic003/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern MagicTaskFuncs D_801EEC18;

extern BattleHandlerTable5 D_801EEC04;

void func_801EF324(void);
void func_801EF708(void);

extern u8           D_801463D6;
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0B38[];
#define BMAGIC_EFFECT_SLOTS D_801F0B38
#define BMAGIC_EFFECT_COUNT 32

#endif
