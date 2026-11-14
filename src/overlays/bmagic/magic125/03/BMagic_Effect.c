#include "magic125_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_PlayOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            func_801EFB48();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

MATCH void func_801EED04(void) {
    u8 slot;
    u8 i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 92);
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_Task->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 92);
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].arg.unk_09   = 9;
    g_Task->param.unk_0B += 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEC0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF04(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 2), 2, g_Task);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        if ((g_FrameCount & 0x1) == 0) {
            g_Task->unk_5D = (RANDOM_MASK(3)) + 4;
            g_Task->unk_5E = (RANDOM_MASK(3)) + 4;
            g_Task->unk_5F = (RANDOM_MASK(3)) + 4;
        }
        Effect_SetActorMatrix();
        func_801EF258();
        func_801EF508();
        PopMatrix();
    }
}

MATCH void func_801EEFF8(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x04000000;
        g_Task->unk_5D      = (RANDOM_MASK(3)) + 4;
        g_Task->unk_5E      = (RANDOM_MASK(3)) + 4;
        g_Task->unk_5F      = (RANDOM_MASK(3)) + 4;
        g_Task->unk_14      = 0x100;
        g_Task->unk_09      = 0x10;
        g_Task->timer       = 8;
        g_Task->header.step += 1;
    }
}

/* func_801EF0F8 */
MATCH void Effect_Rise(void) {
    PartyMember* work  = g_Task;
    u8           timer = work->timer - 1;
    work->timer        = timer;
    work->pos.z.fixed += TO_COORD(-128);
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF148(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->unk_14 += 0x20;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF258(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800000.view.effect.params[3] = (s8)g_Task->unk_5D * g_Task->unk_09;
    D_1F800000.view.effect.params[4] = (s8)g_Task->unk_5E * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5F * g_Task->unk_09;
    for (i = 1; i <= 16; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        setVector(&D_1F800014[2], FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]), FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]), 0);
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        prim             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        setRGB1(prim, 0x10, 0x10, 0x10);
        setRGB2(prim, 0x10, 0x10, 0x10);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EF508(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;

    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800000.view.effect.params[3] = (s8)g_Task->unk_5D * g_Task->unk_09;
    D_1F800000.view.effect.params[4] = (s8)g_Task->unk_5E * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5F * g_Task->unk_09;
    for (i = 1; i <= 32; i++) {
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[0].vz = -0x300;
        D_1F800014[2].vx = D_1F800014[1].vx;
        D_1F800014[2].vy = D_1F800014[1].vy;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 7), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 7), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz = -0x300;
        D_1F800014[3].vx = D_1F800014[1].vx;
        D_1F800014[3].vy = D_1F800014[1].vy;
        D_1F800014[3].vz = 0;
        x                = (D_1F800014[1].vx << 9) + g_Task->pos.x.fixed;
        y                = (D_1F800014[1].vy << 9) + g_Task->pos.y.fixed;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
        Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_AddCellPrim(x, y, 0, sizeof(POLY_G4));
    }
}

MATCH void func_801EF808(void) {
    SYS_DISPATCH_BYTE(D_801F05EC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF508();
        PopMatrix();
    }
}

MATCH void func_801EF890(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->unk_5D      = 0xF;
        g_Task->unk_5E      = 0xF;
        g_Task->unk_5F      = 0xF;
        g_Task->unk_14      = 0x100;
        g_Task->unk_20      = 0x21;
        g_Task->unk_09      = 0x10;
        g_Task->timer       = 30;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF960(void) {
    PartyMember* battler;
    s32          speed;
    u8           i;
    u8           slot;

    speed = g_Task->unk_20;
    if (speed != 1) {
        g_Task->unk_20 = speed - 2;
    }
    g_Task->unk_14 -= g_Task->unk_20;
    if (g_Task->unk_14 < 0x30) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x01));
        for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
            slot                                   = BMagic_AllocEffect();
            battler                                = g_BattleEffectBattler;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (i / 6) * 8 + (rand() & 7) + 1;
            g_BattleEffectBattler->param.unk_0B += 1;
        }
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFAB0(void) {
    s32 level;
    u8  counter;

    level = g_Task->unk_14;
    if (level >= 9) {
        g_Task->unk_14 = level - 1;
    }
    if (g_FrameCount & 0x1) {
        counter        = g_Task->unk_09 - 1;
        g_Task->unk_09 = counter;
        if (!(counter & BYTE_MASK)) {
            BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
            func_801E5988();
        }
    }
}

MATCH void func_801EFB48(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 8), 1, g_Task);
}

MATCH void func_801EFB8C(void) {
    s32 tpage;

    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 9), g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        tpage = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        func_800AF764();
        func_801EFFC8();
        func_801F020C();
        tpage = getTPage(0, 0, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    }
}

INCLUDE_ASM(func_801EFCE4);

INCLUDE_ASM(func_801EFE8C);

MATCH void func_801EFFC8(void) {
    POLY_G3* prim;
    s32      i;

    D_1F800000.view.effect.params[0] = g_Task->timer;
    D_1F800014[0].vx                 = g_Task->unk_2E.half + FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vy                 = g_Task->unk_30.half + FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800000.view.effect.params[3] = (s8)g_Task->unk_5D * 16;
    D_1F800000.view.effect.params[4] = (s8)g_Task->unk_5E * 16;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5F * 16;
    for (i = 1; i < 9; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY2(prim, g_Task->unk_2E.half, g_Task->unk_30.half, D_1F800014[0].vx, D_1F800014[0].vy);
        D_1F800014[0].vx = g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        prim->x2         = D_1F800014[0].vx;
        D_1F800014[0].vy = g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        prim->y2         = D_1F800014[0].vy;
        setRGB0(prim, 0xF0, 0xF0, 0xF0);
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH void func_801F020C(void) {
    POLY_G4* prim;
    s32      i;

    D_1F800000.view.effect.params[0] = g_Task->timer;
    D_1F800000.view.effect.params[1] = g_Task->timer * 2;
    D_1F800014[0].vx                 = g_Task->unk_2E.half + FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
    D_1F800014[0].vy                 = g_Task->unk_30.half + FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
    D_1F800014[1].vx                 = g_Task->unk_2E.half + FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = g_Task->unk_30.half + FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    for (i = 1; i < 9; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, D_1F800014[0].vx, D_1F800014[0].vy);
        prim->x2         = D_1F800014[1].vx;
        prim->y2         = D_1F800014[1].vy;
        D_1F800014[0].vx = g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[1]);
        prim->x1         = D_1F800014[0].vx;
        D_1F800014[0].vy = g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[1]);
        prim->y1         = D_1F800014[0].vy;
        D_1F800014[1].vx = g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        prim->x3         = D_1F800014[1].vx;
        D_1F800014[1].vy = g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        prim->y3         = D_1F800014[1].vy;
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

/* func_801F0524 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0588 */
#include "overlays/bmagic/Actor_Clear.h"
