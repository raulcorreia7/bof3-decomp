#ifndef OVERLAY_WORLD02_AREA077_14_H
#define OVERLAY_WORLD02_AREA077_14_H

/* The world02/area077/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

#include "shared/WorldSpin.h"

#define AREA_SPIN_RADIUS     32
#define AREA_SPIN_PITCH      RANDOM_MASK(0x3FF)
#define AREA_SPIN_SCALE_MASK 0xf
#define AREA_SPIN_SCALE_BASE 1
#define AREA_SPIN_FADE       0

extern s16      D_800E4800;
extern WorldPos D_80146954;
extern u16      D_800E5500;
extern u8       D_800E5502;

/* One of the 64 slots at AREA_WORK, 0x34 bytes each. */
typedef struct AreaSlot {
    Point3l pos; /* 0x00 */
    u8      unk_0C[0x24];
    u16     unk_30; /* 0x30 */
    u16     pad_32; /* 0x32 */
} AreaSlot;

ASSERT_SIZE(AreaSlot, 0x34);

#define AREA_SLOT_COUNT 64

extern u8  D_801F6250[];
extern u8  D_801F6278[];
extern u8  D_801F627D[];
extern u8  D_801F62EC[];
extern u16 D_801F6B1C[];
extern u8  D_801F6B28[];
extern u8  D_801F6B30[];
extern u8  D_801F6B38[];
extern u8  D_801F6B40[];
extern u8  D_801F6B48[];
extern u8  D_801F6B50[];
extern u8  D_801F6B58[];
extern u8  D_801F6B6C;
extern u8  D_801F6B70;
extern u8  D_801F6B74;

void       func_801F3778(s32 arg0, void* dst, RECT* rect);
/* The two sprite tables the step draws index by the timer's low two bits. */
extern s32 D_801F62CC[];
extern s32 D_801F62DC[];
/* The spin-step draw reads six arguments from its two callers; the shared area.h cannot carry it
 * because three other images give func_801F35E0 no arguments. */
void       func_801F35E0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
void       func_801F3CB8(void);
void       func_801F41B4(void);
void       func_801F3B48(Point2s* pos, u8 shade);
void       func_801F30E8(s16 x0, s16 y0, s16 x1, s16 y1);
void       func_801F3BC4(s16 x, s16 y, s16 w, s16 h);

void func_801F529C(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);

extern void func_801F54B8(void);

void Actor_InitSlot(s32 type);
void func_801F462C(s32* pos, s16 radius, u8 center_shade, u8 rim_shade);

/* func_801F3198 */
void GFX_AddBlendDrawMode(u8 blend_mode);

#endif
