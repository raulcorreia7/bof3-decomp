#ifndef OVERLAY_BATTLE_BATL_END_00_H
#define OVERLAY_BATTLE_BATL_END_00_H

#include "overlays/battle/battle.h"
#include <stdio.h>

extern volatile u16 D_801463B0;
extern char         D_80149118[];
extern u8*          D_801EB4F4;
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
/* func_801F09F4 */
extern void         Battle_DrawVictoryZenny(void);

#endif
