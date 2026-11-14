#ifndef OVERLAY_BMAGIC_MAGIC108_03_H
#define OVERLAY_BMAGIC_MAGIC108_03_H

/* The bmagic/magic108/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The four diamond corners RotTransPers4 projects. */

#define EFFECT_TICK_INCREMENT 8
#define EFFECT_TICK_LIMIT     0x80

void func_800AF3A0(s32, s32, s32, s32, s32);

extern Callback D_801EFC9C[];

void func_801EF180(void);
void func_801EF2D4(void);
void func_801EF5C0(void);
void func_801EF6C0(void);

#endif
