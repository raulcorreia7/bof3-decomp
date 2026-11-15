#ifndef OVERLAY_BMAGIC_MAGIC114_03_H
#define OVERLAY_BMAGIC_MAGIC114_03_H

/* The bmagic/magic114/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801EEC04[];
extern Callback D_801F1230[];
extern s32      D_801F11F4[][2];

void func_800AF0F8(s32 pos_x, s32 pos_y, s32* values, u8* base, u8 count, u8 size, u8 seed);
void func_801EF128(void);
void func_801EF280(s32* values);
void func_801F04D4(s32 semi);
void func_801F0FBC(void);
void func_801EFA80(void);

void func_801F0004(void);
void func_801F093C(void);

#endif
