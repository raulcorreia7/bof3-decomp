#ifndef OVERLAY_BMAGIC_MAGIC078_03_H
#define OVERLAY_BMAGIC_MAGIC078_03_H

/* The bmagic/magic078/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The ring angles the leech bands step through: the segment azimuths (D_801F089C), the same row
 * one sector on (D_801F08A4) and the two band start angles (D_801F08B8). */
extern s32 D_801F089C[];
extern s32 D_801F08A4[];
extern s32 D_801F08B8[];

void func_800AF0F8(s32 pos_x, s32 pos_y, s32* values, u8* base, u8 count, u8 size, u8 seed);
void func_801EECFC(void);
void Effect_PlayOnIdleTick(void);
void func_801EFE14(LINE_F4* prim, s32* out, SVECTOR v0, SVECTOR v1, SVECTOR v2, SVECTOR v3);
void func_801EFEB8(void);
void func_801F02FC(void);

#endif
