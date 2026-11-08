#ifndef OVERLAY_WORLD02_AREA077_14_H
#define OVERLAY_WORLD02_AREA077_14_H

/* The world02/area077/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"

#include "shared/WorldSpin.h"

#define AREA_SPIN_RADIUS     32
#define AREA_SPIN_PITCH      RANDOM_MASK(0x3FF)
#define AREA_SPIN_SCALE_MASK 0xf
#define AREA_SPIN_SCALE_BASE 1
#define AREA_SPIN_FADE       0

extern s16 D_800E4800;
extern u8  D_801F6250[];
extern u8  D_801F62EC[];
extern u16 D_801F6B1C[];
extern u8  D_801F6B28[];
extern u8  D_801F6B30[];
extern u8  D_801F6B38[];
extern u8  D_801F6B40[];
extern u8  D_801F6B48[];
extern u8  D_801F6B50[];
extern u8  D_801F6B58[];

void func_801F3778(s32 arg0, void* dst, RECT* rect);
void func_801F3B48(void* dst, s32 size);

void func_801F529C(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);

extern void func_801F54B8(void);

void Actor_InitSlot(s32 type);

/* func_801F3198 */
void GFX_AddBlendDrawMode(u8 blend_mode);

#endif
