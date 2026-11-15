#ifndef OVERLAY_BMAGIC_MAGIC110_03_H
#define OVERLAY_BMAGIC_MAGIC110_03_H

/* The bmagic/magic110/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;

/* The scratch shade the screen fade draws with. */
extern s16 D_1F800004;

extern Callback D_801F0478[];
extern Callback D_801F048C[];

extern Callback D_801F049C[];
void            func_801F0138(void);
void            func_801F01E8(void);

void func_801EF148(void);

#endif
