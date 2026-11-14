#include "magic083_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

/* Clears the effect slot table, then spawns one effect on each selectable battler of the targeted side at its position, and copies the first 32 colours of palette row 26 back from the arena. */
MATCH void func_801EED04(void) {
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u8           slot;
    u8           count;
    u8           index;
    u8           i;

    count = 0;
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    g_Task->unk_04       = func_801EF0CC();
    g_Task->param.unk_0B = 0;
    g_Task->header.mode++;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            index = i + 3;
            if (!(Battle_SlotIsBlocked(index) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 34) & BYTE_MASK;
                owner                              = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].target.party = owner;
                g_BattleEffects[slot].unk_04       = g_Task->unk_04;
                g_BattleEffects[slot].unk_0B       = count;
                g_BattleEffects[slot].arg.unk_09   = (count * 16) + 1;
                g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;
                g_Task->param.unk_0B++;
                count++;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 34) & BYTE_MASK;
                owner                              = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].target.party = owner;
                g_BattleEffects[slot].unk_04       = g_Task->unk_04;
                g_BattleEffects[slot].unk_0B       = count;
                g_BattleEffects[slot].arg.unk_09   = (count * 16) + 1;
                g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;
                g_Task->param.unk_0B++;
                count++;
            }
        }
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF0CC(void) {
    if (*((u8*)&g_Battle.action_type) != BATTLE_ACTION_ABILITY && *((u16*)&g_Battle.action_id) == 0x136) {
        g_Battle.action_id = ABILITY_SHIELD;
    }
    return 0;
}

/* func_801EF108 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF14C(void) {
    SYS_DISPATCH_BYTE(D_801F0EF0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFB24();
        func_801EF844();
        PopMatrix();
    }
}

MATCH void func_801EF1DC(void) {
    void* battler;
    u8    count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = &g_BattleEnemyBattlers[g_Task->unk_03];
        } else {
            battler = &g_Game.members[g_Task->unk_03];
        }
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF2F8(void) {
    PartyMember* owner;
    u8           slot;
    u8           base;
    u8           i;

    if (g_PaletteFades[g_Task->timer].offset.red != 8) {
        g_PaletteFades[g_Task->timer].offset.red++;
        g_PaletteFades[g_Task->timer].offset.green++;
        g_PaletteFades[g_Task->timer].offset.blue++;
    }
    if (++g_Task->unk_09 == 16) {
        base                 = g_Task->param.unk_0B;
        g_Task->param.unk_0B = 0;
        for (i = 0; i < 3; i++) {
            slot = BMagic_AllocEffect();
            if (slot != 0xFF) {
                owner                                  = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].header.step  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_03       = base + (i << 4);
                BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
                BMAGIC_EFFECT_SLOTS[slot].unk_04       = g_Task->unk_04;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i * 10;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 8 + 1;
                BMAGIC_EFFECT_SLOTS[slot].unk_0A       = 1;
                g_Task->param.unk_0B++;
            }
        }
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_StepOnZeroTick.h"

MATCH void func_801EF55C(void) {
    PartyMember* battler;
    u8           slot;

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        slot    = g_Task->unk_03 + 3;
        battler = (PartyMember*)&g_BattleEnemyBattlers[g_Task->unk_03];
    } else {
        slot    = g_Task->unk_03;
        battler = &g_Game.members[slot];
    }
    if (g_PaletteFades[g_Task->timer].offset.red != 0) {
        g_PaletteFades[g_Task->timer].offset.red--;
        g_PaletteFades[g_Task->timer].offset.green--;
        g_PaletteFades[g_Task->timer].offset.blue--;
    }
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(battler);
        func_800AF814(slot);
        func_800AEEC8(g_Task->unk_04, g_Task->unk_03);
        g_Task->param.unk_0B++;
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF844(void) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;
    long     depth;
    long     flag;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    GFX_AddDitheredDrawMode(5, tpage);
    D_1F800000.view.effect.params[3] = g_Task->unk_09 * 5;
    D_1F800000.view.effect.params[4] = D_801F0ED4[g_Task->unk_04][0] * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = D_801F0ED4[g_Task->unk_04][1] * g_Task->unk_09;
    D_1F800000.view.effect.params[6] = D_801F0ED4[g_Task->unk_04][2] * g_Task->unk_09;
    D_1F800014[2].vx                 = (u32)rsin(0) >> 5;
    D_1F800014[2].vy                 = (u32)rcos(0) >> 5;
    for (i = 1; i < 17; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = (u32)rsin(i << 8) >> 5;
        D_1F800014[2].vy = (u32)rcos(i << 8) >> 5;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        poly             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, &depth, &flag);
        poly->r0 = D_1F800000.view.effect.params[3];
        poly->g0 = D_1F800000.view.effect.params[3];
        poly->b0 = D_1F800000.view.effect.params[3];
        poly->r1 = D_1F800000.view.effect.params[4];
        poly->g1 = D_1F800000.view.effect.params[5];
        poly->b1 = D_1F800000.view.effect.params[6];
        poly->r2 = D_1F800000.view.effect.params[4];
        poly->g2 = D_1F800000.view.effect.params[5];
        poly->b2 = D_1F800000.view.effect.params[6];
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    GFX_AddDitheredDrawMode(5, tpage);
}

MATCH void func_801EFB24(void) {
    POLY_G4* poly;
    s32      tpage;
    s32      i;
    long     depth;
    long     flag;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    GFX_AddDitheredDrawMode(5, tpage);
    D_1F800000.view.effect.params[4] = D_801F0EE0[g_Task->unk_04][0] * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = D_801F0EE0[g_Task->unk_04][1] * g_Task->unk_09;
    D_1F800000.view.effect.params[6] = D_801F0EE0[g_Task->unk_04][2] * g_Task->unk_09;
    D_1F800014[1].vx                 = (u32)rsin(0) >> 5;
    D_1F800014[1].vy                 = (u32)rcos(0) >> 5;
    D_1F800014[3].vx                 = (u32)rsin(0) >> 4;
    D_1F800014[3].vy                 = (u32)rcos(0) >> 4;
    for (i = 1; i < 17; i++) {
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[1].vx = (u32)rsin(i << 8) >> 5;
        D_1F800014[1].vy = (u32)rcos(i << 8) >> 5;
        D_1F800014[3].vx = (u32)rsin(i << 8) >> 4;
        D_1F800014[3].vy = (u32)rcos(i << 8) >> 4;
        D_1F800014[3].vz = 0;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        poly             = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3, &depth, &flag);
        poly->r0 = D_1F800000.view.effect.params[4];
        poly->g0 = D_1F800000.view.effect.params[5];
        poly->b0 = D_1F800000.view.effect.params[6];
        poly->r1 = D_1F800000.view.effect.params[4];
        poly->g1 = D_1F800000.view.effect.params[5];
        poly->b1 = D_1F800000.view.effect.params[6];
        poly->r2 = 1;
        poly->g2 = 1;
        poly->b2 = 1;
        poly->r3 = 1;
        poly->g3 = 1;
        poly->b3 = 1;
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    GFX_AddDitheredDrawMode(5, tpage);
}

MATCH void func_801EFE54(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

MATCH void func_801EFE98(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 2, g_Task);
}

INCLUDE_ASM(func_801EFEDC);

MATCH void func_801F0010(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;
    PartyMember* reset;

    Battle_ProjectRange();
    func_801F0BA8((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F050C();
    PopMatrix();
    if (g_FrameCount & 0x1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        reset         = g_Task;
        reset->unk_14 = -0x10;
        reset->timer  = 8;
        reset->unk_20 = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0104(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;

    Battle_ProjectRange();
    func_801F0BA8((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F050C();
    PopMatrix();
    if (g_FrameCount & 0x1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        g_Task->timer = 28 - g_Task->param.unk_0B;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F01F8(void) {
    s32 value;
    s32 value2;
    s32 value3;
    u8  value4;
    u8  value5;

    Battle_ProjectRange();
    if ((g_Task->unk_0C == 4) && (g_Task->timer < 5U)) {
        value2 = (RANDOM_MASK(3)) | 0x40;
    } else {
        value2 = (RANDOM_MASK(3)) | 0x18;
    }
    func_801F0BA8(value2);
    Effect_SetActorMatrix();
    func_801F050C();
    PopMatrix();
    if (g_Task->unk_0C < 4) {
        value          = g_Task->unk_10 + 1;
        g_Task->unk_10 = value;
        if (!(value & 0x7)) {
            g_Task->unk_0C += 1;
        }
    }
    g_Task->unk_09 += g_Task->unk_0C;
    if (g_Task->unk_0C == 4) {
        value4        = g_Task->timer - 1;
        g_Task->timer = value4;
        if (!(value4 & BYTE_MASK)) {
            value5 = g_Task->unk_03;
            if (!(value5 & 0xF0)) {
                value3 = 0x102;
                if (value5 & 0x1) {
                    value3 = 0x101;
                }
                SND_QueueSelectionFx(value3);
            }
            g_Task->unk_10 = 8;
            g_Task->unk_14 = 8;
            g_Task->unk_20 = 8;
            g_Task->header.step += 1;
        }
    }
}

INCLUDE_ASM(func_801F038C);

MATCH void func_801F050C(void) {
    POLY_G3* prim;
    u8*      start;
    s32      depths[16];
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;
    s32      x;
    s32      y;
    s16      angle;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
    start = g_GfxPrimCursor;
    for (i = g_Task->unk_09; i < g_Task->unk_09 + 32; i += 8) {
        D_1F800000.view.effect.params[1] = 0x50;
        D_1F800000.view.effect.params[0] = 0x30;
        D_1F800000.view.effect.params[7] = (i - g_Task->unk_09) / 8;
        D_1F800000.view.effect.params[4] = D_801F0E74[g_Task->unk_04][D_1F800000.view.effect.params[7]][0];
        D_1F800000.view.effect.params[5] = D_801F0E74[g_Task->unk_04][D_1F800000.view.effect.params[7]][1];
        D_1F800000.view.effect.params[6] = D_801F0E74[g_Task->unk_04][D_1F800000.view.effect.params[7]][2];
        D_1F800014[0].vx                 = 0;
        D_1F800014[0].vy                 = 0;
        D_1F800014[0].vz                 = D_1F800000.view.effect.params[1];
        angle                            = i & 0x1F;
        D_1F800000.view.effect.params[2] = angle << 7;
        D_1F800014[1].vx                 = FIXED_MUL(rsin(angle << 7), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = 0;
        angle                            = (i + 8) & 0x1F;
        D_1F800000.view.effect.params[2] = angle << 7;
        D_1F800014[2].vx                 = FIXED_MUL(rsin(angle << 7), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz                 = 0;
        prim                             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        depths[(i - g_Task->unk_09) / 8] = RotAverage3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = g_Task->pos.x.fixed;
    y = g_Task->pos.y.fixed;
    func_800AF0F8(x, y, depths, start, 4, sizeof(POLY_G3), 0);
    start = g_GfxPrimCursor;
    for (i = g_Task->unk_09; i < g_Task->unk_09 + 32; i += 8) {
        D_1F800000.view.effect.params[7] = (i - g_Task->unk_09) / 8;
        D_1F800000.view.effect.params[4] = D_801F0EA4[g_Task->unk_04][D_1F800000.view.effect.params[7]][0];
        D_1F800000.view.effect.params[5] = D_801F0EA4[g_Task->unk_04][D_1F800000.view.effect.params[7]][1];
        D_1F800000.view.effect.params[6] = D_801F0EA4[g_Task->unk_04][D_1F800000.view.effect.params[7]][2];
        D_1F800014[0].vx                 = 0;
        D_1F800014[0].vy                 = 0;
        D_1F800014[0].vz                 = -D_1F800000.view.effect.params[1];
        angle                            = i & 0x1F;
        D_1F800000.view.effect.params[2] = angle << 7;
        D_1F800014[1].vx                 = FIXED_MUL(rsin(angle << 7), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = 0;
        angle                            = (i + 8) & 0x1F;
        D_1F800000.view.effect.params[2] = angle << 7;
        D_1F800014[2].vx                 = FIXED_MUL(rsin(angle << 7), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz                 = 0;
        prim                             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        depths[(i - g_Task->unk_09) / 8] = RotAverage3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = g_Task->pos.x.fixed;
    y = g_Task->pos.y.fixed;
    func_800AF0F8(x, y, depths, start, 4, sizeof(POLY_G3), 0);
}

MATCH void func_801F0BA8(s32 radius) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;

    D_1F800000.view.effect.params[0] = radius;
    i                                = 0;
    do {
        tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        poly = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        poly->x0 = g_Task->unk_2E.half;
        poly->y0 = g_Task->unk_30.half;
        poly->x1 = g_Task->unk_2E.half + ((rsin(i << 9) * D_1F800000.view.effect.params[0]) >> 12);
        poly->y1 = g_Task->unk_30.half + ((rcos(i << 9) * D_1F800000.view.effect.params[0]) >> 12);
        poly->x2 = g_Task->unk_2E.half + ((rsin((i + 1) << 9) * D_1F800000.view.effect.params[0]) >> 12);
        poly->y2 = g_Task->unk_30.half + ((rcos((i + 1) << 9) * D_1F800000.view.effect.params[0]) >> 12);
        poly->r0 = 0x80;
        poly->g0 = 0x80;
        poly->b0 = 0x80;
        poly->r1 = 1;
        poly->g1 = 1;
        poly->b1 = 1;
        poly->r2 = 1;
        poly->g2 = 1;
        poly->b2 = 1;
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 8);
}

/* func_801F0DC0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0E24 */
#include "overlays/bmagic/Actor_Clear.h"
