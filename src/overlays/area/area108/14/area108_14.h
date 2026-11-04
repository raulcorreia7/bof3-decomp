#ifndef OVERLAY_WORLD02_AREA108_14_H
#define OVERLAY_WORLD02_AREA108_14_H

/* The world02/area108/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"
#include <rand.h>

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0x04

typedef struct AreaSprite {
    u8     flags_00;
    u8     flags_01;
    u8     flags_02;
    u8     flags_03;
    s32    origin_x;
    s32    origin_y;
    s32    origin_z;
    u8     unk_10[4];
    VECTOR normal;
    u16    half_size;
} AreaSprite;

ASSERT_SIZE(AreaSprite, 0x28);
ASSERT_OFFSET(AreaSprite, origin_x, 0x04);
ASSERT_OFFSET(AreaSprite, normal, 0x14);
ASSERT_OFFSET(AreaSprite, half_size, 0x24);

typedef struct Area108Scratch {
    u8  unk_00[0x34];
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
} Area108Scratch;

ASSERT_SIZE(Area108Scratch, 0x40);
ASSERT_OFFSET(Area108Scratch, pos_x, 0x34);
ASSERT_OFFSET(Area108Scratch, pos_y, 0x38);
ASSERT_OFFSET(Area108Scratch, pos_z, 0x3C);

/* The game-overlay state bytes the cancel path resets. */
extern u8       D_80147AF0;
extern u8       D_801F56E8[];
extern Callback D_801F56F4[];
extern u8       D_801F56FC[];
extern u8       D_801F5718[];
extern u8       D_801F63C4[];
extern u8*      D_801F63EC;

/* func_8019651C */
s32  GFX_AllocPaletteFade(u8* color_data, s32 palette_base, s32 palette_count, s32 palette_index, s32 flag_value);
void func_801F2D40(const void* sprite);
void func_801F2F1C(void* sprite);
void func_801F2FC8(void);
u8   func_801F321C(void);
void func_801F3BA0(void);
void func_801F3C84(void);
void func_801F55F0(s32);

void Area_ProjectPoint(s32* pos, long* screen_xy);

u8 func_8019601C();

#endif
