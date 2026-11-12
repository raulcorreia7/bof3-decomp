#ifndef OVERLAY_BATTLE_BATL_END_00_H
#define OVERLAY_BATTLE_BATL_END_00_H

#include "overlays/battle/battle.h"
#include <stdio.h>

extern u16        D_801463B0;
extern u16        D_80148628;
extern u16        D_8014862A;
extern u8         D_8014862D;
extern char       D_80149118[];
extern u8*        D_801EB4F4;
extern bool       Item_Add(s32 category, u8 item, u8 amount, s32 unused);
void              func_801ADDD4(s32 char_id);
u8                func_801DB524(u32 slot);
extern const char D_801EEC04[];
extern const char D_801EEC4C[];
extern const char D_801EEC50[];
u8                func_801EEDA8(void);
u16               func_801EF928(u8 id, u8 flag);
s32               func_801EF6C0(void);
extern void       func_801EFE5C(void);
void              func_801F039C(s16 x, s16 y, s32 width, s32 height);
extern void       func_801F07C0(void);
extern void       func_801F07E0(void);
extern Callback   D_801F0C98[];
extern Callback   D_801F0CA4[];
extern Callback   D_801F0CB8[];
extern Callback   D_801F0CC0[];
extern char       D_801F0CD0[];
extern u8         D_801F0CD4[]; /* item icon texture index, by Item_GetIcon result */
extern void       func_801F09D4(void);
/* func_801F09F4 */
extern void       Battle_DrawVictoryZenny(void);
void              func_801F0A74(s16 x, s16 y, u8 clut, u8 category, u8 item, u8 amount, u8 shade);

#endif
