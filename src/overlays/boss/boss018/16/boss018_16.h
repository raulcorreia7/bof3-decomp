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
extern u8       D_800C2C5C[];
extern u8       D_800C2C68[];
extern u8       D_800C2C74[];
extern u8       D_800C2C80[];
extern u16      D_800C2C8C[];
extern u16      D_800C2C94[];
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
extern u8       D_80145F09[];
extern u8       D_80145FA8;
extern u16      D_801FD6FE;
/* Frame-state word owned by the main executable; the boss018 step reads bit 0. */
extern u16      D_801FD700;
extern u8       D_800C2C50;
extern u16      D_800C2C9C;
extern u16      D_800C2CA4;
extern u16      D_801FD6FC;
extern u16      D_801FD702;

void func_800AC870(s32 entry_id, PartyBattler* source_record, s32 mode);
void func_800C197C(s32 mode);
void func_800C1C6C(s32 mode);
void func_800C29AC(s32 arg0, s32 arg1);

void func_800C2074(s32 mode);

#endif
