#ifndef OVERLAY_BMAGIC_MAGIC116_03_H
#define OVERLAY_BMAGIC_MAGIC116_03_H

/* The bmagic/magic116/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleEffect*       D_801EC2E0;
extern BattleHandlerTable4 D_801EEC04;

/* The guard the record reset waits on, the battle flag it raises, and the
 * request hand-off that follows. */
u8 func_801EF118(void);

extern u8 D_801EF2A8[];

void func_801EF020(s32 arg0);

#endif
