#ifndef OVERLAY_BMAGIC_MAGIC086_03_H
#define OVERLAY_BMAGIC_MAGIC086_03_H

/* The bmagic/magic086/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;
extern SVECTOR           D_1F800014[];
/* The first scratchpad word: the ring radius func_801EF424 stages. */
extern s32               D_1F800000_WORD[];
extern Callback          D_801F0360[];

void func_801EF424(void);

extern Callback D_801F036C[];
void            func_801EF9E0(void);

extern Callback D_801F0384[];
void            func_801F01A8(void);

#endif
