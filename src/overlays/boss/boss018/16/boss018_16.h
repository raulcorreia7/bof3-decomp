#ifndef OVERLAY_BOSS_BOSS018_16_H
#define OVERLAY_BOSS_BOSS018_16_H

/* The boss/boss018/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

#define g_SceneFlags ((void*)g_SceneFlags)

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss018/16] of config/symbols.toml. */

extern u8       D_800C2C38[];
extern u8       D_800C2C44[];
extern u8       D_800C2C50;
extern u8       D_800C2C5C[];
extern u8       D_800C2C68[];
extern u8       D_800C2C74[];
extern u8       D_800C2C80[];
extern u16      D_800C2C8C[];
extern u16      D_800C2C94[];
extern u16      D_800C2C9C;
extern u16      D_800C2CA4;
extern Callback D_800C2CAC[];
extern Callback D_800C2CDC[];
extern Callback D_800C2CE8[];
extern Callback D_800C2D18[];
extern Callback D_800C2D24[];
extern Callback D_800C2D54[];
extern Callback D_800C2D60[];
extern Callback D_800C2D94[];
extern Callback D_800C2DAC[];
extern Callback D_800C2DB8[];
/* The stamped block's corner: one map cell per pattern. */
typedef struct Boss018MapCell {
    u8 column;
    u8 row;
} Boss018MapCell;

ASSERT_SIZE(Boss018MapCell, 2);
ASSERT_OFFSET(Boss018MapCell, column, 0x00);
ASSERT_OFFSET(Boss018MapCell, row, 0x01);

extern Boss018MapCell D_800C2DC4[];
extern u32            D_800C2DC8[];
extern u16      D_801EB6C4;
extern u16      D_801EB6C6;
extern u16      D_801EB7DC;
extern u16      D_801EB8F4;
extern u16      D_801FD6FC;
extern u16      D_801FD6FE;
/* Frame-state word owned by the main executable; the boss018 step reads bit 0. */
extern u16      D_801FD700;
extern u16      D_801FD702;

void func_800C197C(s32 mode);
void func_800C1C6C(s32 mode);
void func_800C2074(s32 mode);

void func_800C29AC(s32 base, s32 pattern);

void func_800C2A40(void);

#endif
