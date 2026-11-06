#ifndef OVERLAY_BATTLE_BATL_END_00_H
#define OVERLAY_BATTLE_BATL_END_00_H

#include "overlays/battle/battle.h"
#include "work/save.h"
#include <stdio.h>

extern u8           D_80145F16[][BATTLE_PARTY_STRIDE];
extern u8           D_80145F17[][BATTLE_PARTY_STRIDE];
/* D_801462E3 */
extern u8           g_BattleUIStep;
/* D_801462F0 */
extern u8           g_BattlePartyCount;
extern volatile u16 D_801463B0;
extern char         D_80149118[];
extern u8*          D_801EB4F4;
extern bool         Item_Add(s32 category, u8 item, u8 amount, s32 unused);
u8                  func_801DB524(u32 slot);
extern const char   D_801EEC04[];
extern const char   D_801EEC4C[];
u8                  func_801EEDA8(void);
u16                 func_801EF928(u8 id, u8 flag);
extern void         func_801EFE5C(void);
extern void         func_801F07C0(void);
extern void         func_801F07E0(void);
extern Callback     D_801F0C98[];
extern Callback     D_801F0CA4[];
extern Callback     D_801F0CB8[];
extern Callback     D_801F0CC0[];
extern char         D_801F0CD0[];
extern void         func_801F09D4(void);
extern void         func_801F09F4(void);

#endif
