#include "magic041_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

INCLUDE_ASM(func_801EECB0);

MATCH void func_801EEE14(void) {
    u8            timer;
    PartyMember** selected;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        selected = &g_Battle.selected_actor;
        GFX_FreePaletteFadeTarget(*selected);
        g_Task->unk_09 = GFX_AllocPaletteFade(*selected, 0, 0, 0, 1);
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEB4(void) {
    u8 timer;

    g_PaletteFades[g_Task->unk_09].offset.red += 2;
    g_PaletteFades[g_Task->unk_09].offset.green += 1;
    g_PaletteFades[g_Task->unk_09].offset.blue += 1;
    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 8) {
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_NextStepOnWorkLastTick.h"

MATCH void func_801EEFF8(void) {
    g_PaletteFades[g_Task->unk_09].offset.red -= 2;
    g_PaletteFades[g_Task->unk_09].offset.green -= 1;
    g_PaletteFades[g_Task->unk_09].offset.blue -= 1;
    if (--g_Task->timer == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF190 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF1D4(void) {
    Magic041Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF670();
        PopMatrix();
    }
}

MATCH void func_801EF27C(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        src              = g_BattleEffectBattler;
        dst              = g_Task;
        dst->pos.x.fixed = src->pos.x.fixed;
        dst->pos.y.fixed = src->pos.y.fixed;
        dst->pos.z       = src->pos.z;
        dst->unk_09      = 0;
        g_Task->timer    = 0;
        g_Task->header.step++;
    }
}

MATCH void func_801EF308(void) {
    u8 timer;

    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if (timer == 32) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF358(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->unk_09 += 4;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        func_801E5988();
    }
}

MATCH void func_801EF3D0(void) {
    Magic041SecondSteps handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFAB8();
        PopMatrix();
    }
}

MATCH void func_801EF484(void) {
    PartyMember* src;

    src                 = (PartyMember*)g_BattleEffectBattler;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 0;
    g_Task->header.step = g_Task->header.step + 1;
}

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF670);

MATCH void func_801EFAB8(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = 0x88;
    D_1F800000.view.effect.params[3] = g_Task->unk_09 << 3;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[1].vz                 = 0;
    D_1F800014[0].vz                 = 0;

    for (i = 1; i <= 16; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3] / 4, D_1F800000.view.effect.params[3] / 4);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3] / 4, D_1F800000.view.effect.params[3] / 4);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }

    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}
