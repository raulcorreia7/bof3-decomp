#ifndef OVERLAY_BMAGIC_MAGIC062_03_H
#define OVERLAY_BMAGIC_MAGIC062_03_H

/* The bmagic/magic062/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"
#include "overlays/battle/battle/15/battle_15.h"

extern BMagicEffectFuncs D_801EEC04;

extern Callback D_801F0C18[];
void            func_801EF2F0(s32 selector);
void            func_801EF934(void);

void      func_801F026C(void);
/* The disc colours by effect kind and ring: red, green and blue. */
extern u8 D_801F0BA4[][4][3];
extern u8 D_801F0BD4[][4][3];
void      func_800AF0F8(s32 pos_x, s32 pos_y, s32* values, u8* base, u8 count, u8 size, u8 seed);

void func_801F0910(s32 arg0);

#endif
