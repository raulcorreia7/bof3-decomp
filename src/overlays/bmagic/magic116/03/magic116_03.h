#ifndef OVERLAY_BMAGIC_MAGIC116_03_H
#define OVERLAY_BMAGIC_MAGIC116_03_H

/* The bmagic/magic116/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern MagicTaskFuncs D_801EEC04;
extern u8             D_801EF2A8[];

/* The guard the record reset waits on, the battle flag it raises, and the
 * request hand-off that follows. */
u8 func_801EF118(void);

extern BattleEffect* D_801EC2E0;

#endif
