#ifndef OVERLAY_WORLD00_AREA008_13_H
#define OVERLAY_WORLD00_AREA008_13_H

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/area/world00.h"
#include "work/area_spad.h"
#include <rand.h>
#include <stdio.h>

#define WORLD00_AREA008_SCRATCH_PTR SP_REF(volatile Actor*, 0x44u)
#define WORLD00_AREA008_STATE_PTR   (*(volatile Actor**)&g_GameState)
#define g_CurrentActor              (*(s32*)&g_CurrentActor)

/* The world overlay's reading of the shared field work row. */

extern u8          D_8014601A;
extern u16         D_80146028;
extern volatile u8 D_801460E8;
extern u16         D_80146876[];
extern s32         D_80146C4C;
extern char        D_801F2C14[3];
extern u8          D_801F4674[12];
extern u8          D_801F4680[8];
extern Callback    D_801F46B0[15];
extern Callback    D_801F46EC[3];
extern u8          D_801F46F8[3320];
extern u16         D_801F53F0[2];
extern volatile u8 D_801F53F4;
extern u8          D_801F53F5;
extern u8          D_801F53F6;
extern u8          D_801F53F7;
extern char        WORLD00_AREA008_D_801F2C04[];
extern char        WORLD00_AREA008_D_801F2C10[];
extern Callback    g_AreaWorkStates[10];

void func_801F2D24(void);
void func_801F2F78(void);
void func_801F3010(void);
void func_801F30B8(void);
void func_801F317C(void);
void func_801F31D0(void);
void func_801F3288(void);
void func_801F32AC(void);
void func_801F3344(void);
void func_801F33F0(void);
void func_801F34FC(void);
void func_801F357C(void);
void func_801F3654(void);
void func_801F365C(void);
void func_801F36DC(void);
void func_801F37B4(void);
void func_801F37BC(void);
void func_801F39B4(void);
void func_801F3AA8(void);
void func_801F3AE8(void);
void func_801F3BB4(void);
void func_801F3C2C(void);
void func_801F3D18(void);
void Menu_DrawHeaderBar(s16 x, s16 y, s32 width, s32 height, u8 window_style);
void func_801F42D4(void);
void func_801F4334(void);
void func_801F437C(void);
void func_801F43C8(void);
void func_801F4424(void);
void func_801F450C(void);
void func_801F4578(void);
void func_801F45A0(void);
void Area_ResetViewOffsetY(void);
void func_801F45E4(void);
void func_801F4600(void);
void func_801F461C(void);

/* Select the work mode from the area flag bytes: mode 9 when bit 7 is set,
 * else mode 5 when the second byte is 3. */
static inline void FieldSelectDrawMode(void) {
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        g_SpadWork->unk_01 = 9;
        return;
    }
    if (g_ScriptVars[2] == 3) {
        g_SpadWork->unk_01 = 5;
    }
}

/* Clear the mode guard, mark the slot live, point the work pointer at the
 * indexed row and hand control to the area script. */
static inline void FieldActivateActor(void) {
    Actor* s;
    Actor* e;
    s32    idx;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        g_SpadWork->unk_01 = 0x0E;
        return;
    }
    s = &g_Actors[g_SpadWork->unk_0B];
    s->flags_00 |= 0x40;
    s               = g_SpadWork;
    idx             = s->unk_0B;
    g_ScriptVars[2] = 3;
    e               = &g_Actors[idx];
    g_SpadWork      = e;
    Actor_SelectScript(1);
    s->unk_01  = 1;
    g_SpadWork = s;
}

#endif
