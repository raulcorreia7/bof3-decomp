#include "magic130_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* work;
    u32          slot;
    s32          i;
    u16*         dst;
    u16*         src;

    Battle_CenterCamera();
    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 30;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 102) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    g_Task->param.unk_0B += 1;
    for (i = 0; i < 6; i++) {
        slot                               = Battle_AllocEffect(1, 102) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        *dst++ = *src++ | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    g_GfxPalettePending                                      = 1;
    SND_QueueSelectionEffect(0x100);
    SND_QueueSelectionEffect(0x101);
}

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEED4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF18(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    D_801EFA4C[g_Task->header.step]();
    if ((g_Task->header.flags & ACTOR_FLAG_IN_USE) && (g_Task->header.step != 0)) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EEFB4);

MATCH void func_801EF10C(void) {
    g_Task->unk_5D += 8;
    g_Task->unk_5E += 8;
    g_Task->unk_5F += 8;
    if ((s8)g_Task->unk_5D == 0) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

MATCH void func_801EF1E0(void) {
    g_Task->unk_5D -= 8;
    g_Task->unk_5E -= 8;
    g_Task->unk_5F -= 8;
    if ((s8)g_Task->unk_5D == -0x80) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF284(void) {
    SYS_DISPATCH_BYTE(D_801EFA5C, g_Task->header.step);
    GFX_AddDitheredDrawMode(2, getTPage(0, 1, 320, 256));
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF4D4();
        func_801EF730();
    }
}

MATCH void func_801EF354(void) {
    PartyMember* task;
    u16          value;

    task              = g_Task;
    task->unk_2E.half = task->param.unk_0B * 26 + 0x98;
    value             = D_801EFA6C[task->param.unk_0B];
    task->unk_14      = 0x20;
    task->unk_09      = 0x3C;
    task->unk_30.half = value + 0x50;
    g_Task->timer     = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF3DC(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void Effect_CountDownTimerStep2(void) {
    BMAGIC_COUNT_DOWN_TIMER_STEP();
}

#include "overlays/bmagic/Effect_CountDownAndFinish.h"

MATCH void func_801EF4D4(void) {
    POLY_G3* prim;
    s32      i;

    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800000.view.effect.params[2] = g_Task->timer * 8;
    D_1F800000.view.effect.params[3] = g_Task->timer * 8;
    D_1F800000.view.effect.params[4] = g_Task->timer * 4;
    D_1F800000.view.effect.params[5] = g_Task->timer * 8;
    D_1F800014[0].vx                 = g_Task->unk_2E.half + FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vy                 = g_Task->unk_30.half + FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    for (i = 1; i < 9; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.half, g_Task->unk_30.half, D_1F800014[0].vx, D_1F800014[0].vy, D_1F800014[0].vx = g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]),
               D_1F800014[0].vy = g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]));
        setRGB0(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        GFX_AddPrim(2, sizeof(POLY_G3));
    }
}

MATCH void func_801EF730(void) {
    POLY_G4* prim;
    s32      i;

    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800000.view.effect.params[1] = g_Task->unk_14 * 2 + (rand() & 7);
    D_1F800014[0].vx                 = g_Task->unk_2E.half + FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
    D_1F800014[0].vy                 = g_Task->unk_30.half + FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
    D_1F800014[1].vx                 = g_Task->unk_2E.half + FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = g_Task->unk_30.half + FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    for (i = 1; i < 9; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, D_1F800014[0].vx, D_1F800014[0].vy);
        prim->x2 = D_1F800014[1].vx;
        prim->y2 = D_1F800014[1].vy;
        prim->x1 = D_1F800014[0].vx = g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[1]);
        prim->y1 = D_1F800014[0].vy = g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[1]);
        prim->x3 = D_1F800014[1].vx = g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        prim->y3 = D_1F800014[1].vy = g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        GFX_AddPrim(2, sizeof(POLY_G4));
    }
}
