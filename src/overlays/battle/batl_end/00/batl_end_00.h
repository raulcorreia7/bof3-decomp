#ifndef OVERLAY_BATTLE_BATL_END_00_H
#define OVERLAY_BATTLE_BATL_END_00_H

#include "overlays/battle/battle.h"
#include <stdio.h>

extern u16        D_801463B0;
extern u16        D_801463B4;
extern s16        D_80148628;
extern u16        D_8014862A;
extern char       D_80149118[];
extern const char D_801EEC40[4];
extern const char D_801EEC44[];
extern const char D_801EEC48[];
/* func_801ADDD4 */
u32               Char_GetExpToNextLevel(s32 slot);
extern const char D_801EEC04[];
extern const char D_801EEC4C[];
extern const char D_801EEC50[];
u8                func_801EEDA8(void);
/* Sets the reward list's first entry. */
void              func_801DE9A8(u8 entry);
s32               func_801EF6C0(void);
u16               func_801EF928(s32 id, s32 flag);
extern void       func_801EFE5C(void);
void              func_801F039C(s16 x, s16 y, s16 width, s16 height);
/* The battle panel helpers of BATTLE.EMI: a corner or edge shape and the two frame lines. */
void              func_801D9AB4(s16 x, s16 y, s32 shape, s32 shade);
void              func_801DA5A8(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b);
void              func_801DA4B4(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b);
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
