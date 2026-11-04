#ifndef OVERLAY_BATTLE_BATL_END_00_H
#define OVERLAY_BATTLE_BATL_END_00_H

#include "overlays/battle/battle.h"
#include <stdio.h>

/* D_801462E3 */
extern u8           g_BattleUiStep;
/* D_801462F0 */
extern u8           g_BattlePartyCount;
extern u8           D_80145F16[][BATTLE_PARTY_STRIDE];
extern u8           D_80145F17[][BATTLE_PARTY_STRIDE];
extern u32          D_8014632C;
extern volatile u16 D_801463B0;
extern char         D_80149118[];
extern u8*          D_801EB4F4;
u8                  func_801DB524(u32 slot);
u8                  func_801EEDA8(void);
extern const char   D_801EEC04[];
extern const char   D_801EEC4C[];
extern void         func_801EFE5C(void);
extern void         func_801F07C0(void);
extern void         func_801F07E0(void);
extern void         func_801F09D4(void);
extern void         func_801F09F4(void);
extern Callback     D_801F0C98[];
extern Callback     D_801F0CA4[];
extern Callback     D_801F0CB8[];
extern Callback     D_801F0CC0[];
extern char         D_801F0CD0[];
extern bool         Party_AddItem(s32 category, u8 item, u8 amount, s32 unused);
extern void         UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text);

#endif
