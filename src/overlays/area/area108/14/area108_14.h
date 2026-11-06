#ifndef OVERLAY_WORLD02_AREA108_14_H
#define OVERLAY_WORLD02_AREA108_14_H

/* The world02/area108/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "overlays/area/AreaSprite.h"
#include "overlays/area/world02.h"
#include "work/area_spad.h"
#include <rand.h>

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0x04

typedef struct Area108Scratch {
    u8      unk_00[0x34];
    Vec3S32 pos;
} Area108Scratch;

ASSERT_SIZE(Area108Scratch, 0x40);
ASSERT_OFFSET(Area108Scratch, pos, 0x34);

extern u8       D_80145F09;
/* The game-overlay state bytes the cancel path resets. */
extern u8       D_80147AF0;
extern u8       D_801F56E8[];
extern Callback D_801F56F4[];
extern u8       D_801F56FC[];
extern u8       D_801F5718[];
extern u8       D_801F63C4[];
extern u8*      D_801F63EC;

void func_801F2D40(const void* sprite);
void func_801F2F1C(void* sprite);
void func_801F2FC8(void);
u8   func_801F321C(void);
void func_801F3BA0(void);
void func_801F3C84(void);

void func_801F55F0(s32);

s32  func_801F3034(void);
void func_801F34B8(void);

void func_801F4160(s32 arg0, s32 arg1);

#endif
