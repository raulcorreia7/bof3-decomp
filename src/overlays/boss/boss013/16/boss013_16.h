#ifndef OVERLAY_BOSS_BOSS013_16_H
#define OVERLAY_BOSS_BOSS013_16_H

/* The boss/boss013/16 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/boss/boss.h"

/* The scratchpad work area is a PartyBattler record in this image. */
#define g_SpadWork ((PartyBattler*)g_SpadWork)

extern u8           D_800C25F0[];
extern u16          D_800C2618[];
extern Callback     D_800C2620[];
extern Callback     D_800C2650[];
extern Callback     D_800C265C[];
extern Callback     D_800C268C[];
extern Callback     D_800C2698[];
extern Callback     D_800C26C8[];
extern Callback     D_800C26D4[];
extern u8           D_800C26E0;
extern u8           D_80146322;
/* The selection-kind byte: battle/ram.h names the cell as g_BattleActingBattler but
 * declares only the 6375 byte. */
extern u8           g_BattleActingBattler;
extern s32          D_8014632C;
extern u16          D_801EB6B6;
extern u16          D_801EB7CE;
extern PartyBattler D_801EB860;

/* The mode handler sets the image installs into the battle hooks; the
 * addresses are in [emi/boss/boss013/16] of config/symbols.toml. */

u8   func_800C2138(u32 mode);
void func_800C2348(void);
void func_800C243C(void);

#endif
