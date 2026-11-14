#include "magic044_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEDA0);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;
    u32          i;
    u8           slot;

    g_Task->facing = g_BattleEffectBattler->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, 6) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    i   = 1;
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i + AREA_PALETTE_UNIT / sizeof(u16)] = src[i + AREA_PALETTE_UNIT / sizeof(u16)] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW + AREA_PALETTE_UNIT) = 0;

    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE00 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE44(void) {
    SYS_DISPATCH_BYTE(D_801F0A1C, g_Task->header.step);
    if (g_Task->unk_04 != 0) {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EF4E0();
        }
    } else {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EFA4C();
        }
    }
}

INCLUDE_ASM(func_801EEEFC);

MATCH void func_801EF138(void) {
    VECTOR       pos;
    PartyMember* actor;
    s32          diff;
    u8           count;

    count = g_Task->timer;
    if (count < 16) {
        g_Task->timer = count + 1;
    }
    actor  = g_Battle.selected_actor;
    pos.vx = (actor->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (actor->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vz = (actor->pos.z.fixed + 0x800000) >> 17;
    func_800AF3A0(pos, 0xC0);
    g_Task->unk_10 = g_Task->unk_0C;
    g_Task->unk_0C = ratan2(actor->pos.x.fixed - g_Task->pos.x.fixed, actor->pos.y.fixed - g_Task->pos.y.fixed);
    if (func_800AF66C((BattleRange*)actor, 0x8000) != 0) {
        g_Task->pos.x.fixed = actor->pos.x.fixed;
        g_Task->pos.y.fixed = actor->pos.y.fixed;
        g_Task->header.step += 1;
    } else {
        diff           = (g_Task->unk_10 & ANGLE_MASK) - (g_Task->unk_0C & ANGLE_MASK);
        g_Task->unk_10 = diff;
        if (diff < 0) {
            g_Task->unk_10 = ~diff + 1;
        }
        if ((u32)(g_Task->unk_10 - 0x601) < 0x3FF) {
            g_Task->pos.x.fixed = actor->pos.x.fixed;
            g_Task->pos.y.fixed = actor->pos.y.fixed;
            g_Task->header.step += 1;
        }
    }
    Battle_ProjectRange();
    Effect_RecordTrail();
    if (g_Task->header.step != 1 && g_Task->unk_04 == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    }
}

MATCH void func_801EF320(void) {
    PartyMember* work;
    u32          slot;
    u8           count;

    if (g_Task->timer < 0x10) {
        g_Task->param.unk_0B += 1;
        g_Task->timer += 1;
        Battle_ProjectRange();
        Effect_RecordTrail();
    }
    if ((g_FrameCount & 0x3) == 0) {
        slot = Battle_AllocEffect(1, 6) & BYTE_MASK;
        if (slot != GAME_NONE) {
            work                               = g_BattleEffectBattler;
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].target.party = work;
            g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
            g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
            g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
            g_BattleEffectBattler->param.unk_0B += 1;
        }
    }
    count = g_Task->timer;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->unk_09 = count;
        g_Task->header.step += 1;
    }
}

/* func_801EF478 */
#include "overlays/bmagic/Effect_FinishTrail.h"

MATCH void func_801EF4E0(void) {
    POLY_G4* prim;
    s32      k;
    s32      tpage;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    k = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][k].x == -1) {
        k++;
    }
    D_1F800000.view.effect.params[0] = 2;
    D_1F800000.view.effect.params[6] = BMagic_Trail[g_Task->unk_04][k].x;
    D_1F800000.view.effect.params[7] = BMagic_Trail[g_Task->unk_04][k].y;
    D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k + 1].x;
    D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k + 1].y;
    D_1F800000.view.effect.params[1] = ratan2(D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5] - D_1F800000.view.effect.params[7]);
    D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k].x;
    D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k].y;
    for (k = k + 1; k < g_Task->timer; k++) {
        D_1F800000.view.effect.params[6] = D_1F800000.view.effect.params[4];
        D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[5];
        D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k].x;
        D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k].y;
        prim                             = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] + 0x400) & ANGLE_MASK;
        prim->x0                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y0                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] - 0x400) & ANGLE_MASK;
        prim->x2                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y2                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800000.view.effect.params[1] = ratan2(D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5] - D_1F800000.view.effect.params[7]);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] + 0x400) & ANGLE_MASK;
        prim->x1                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y1                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] - 0x400) & ANGLE_MASK;
        prim->x3                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y3                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800000.view.effect.params[2] = 97 - (k - 1) * 6;
        D_1F800000.view.effect.params[3] = 193 - (k - 1) * 12;
        setRGB0(prim, 1, 1, D_1F800000.view.effect.params[3]);
        setRGB2(prim, 1, 1, D_1F800000.view.effect.params[3]);
        D_1F800000.view.effect.params[2] = 97 - k * 6;
        D_1F800000.view.effect.params[3] = 193 - k * 12;
        setRGB1(prim, 1, 1, D_1F800000.view.effect.params[3]);
        setRGB3(prim, 1, 1, D_1F800000.view.effect.params[3]);
        GFX_AddPrim(3, sizeof(POLY_G4));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
}

MATCH void func_801EFA4C(void) {
    POLY_G4* prim;
    s32      k;
    s32      tpage;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = 12;
    k                                = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][k].x == -1) {
        k++;
    }
    D_1F800000.view.effect.params[6] = BMagic_Trail[g_Task->unk_04][k].x;
    D_1F800000.view.effect.params[7] = BMagic_Trail[g_Task->unk_04][k].y;
    D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k + 1].x;
    D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k + 1].y;
    D_1F800000.view.effect.params[1] = ratan2(D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5] - D_1F800000.view.effect.params[7]);
    D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k].x;
    D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k].y;
    for (k = k + 1; k < g_Task->timer; k++) {
        D_1F800000.view.effect.params[6] = D_1F800000.view.effect.params[4];
        D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[5];
        D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k].x;
        D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k].y;
        prim                             = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] + 0x400) & ANGLE_MASK;
        prim->x0                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y0                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->x2                         = D_1F800000.view.effect.params[6];
        prim->y2                         = D_1F800000.view.effect.params[7];
        D_1F800000.view.effect.params[1] = ratan2(D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5] - D_1F800000.view.effect.params[7]);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] + 0x400) & ANGLE_MASK;
        prim->x1                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y1                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->x3                         = D_1F800000.view.effect.params[4];
        prim->y3                         = D_1F800000.view.effect.params[5];
        D_1F800000.view.effect.params[3] = 97 - (k - 1) * 6;
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[3], 1, D_1F800000.view.effect.params[3]);
        D_1F800000.view.effect.params[3] = 97 - k * 6;
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, D_1F800000.view.effect.params[3], 1, D_1F800000.view.effect.params[3]);
        GFX_AddPrim(3, sizeof(POLY_G4));
    }
    k = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][k].x == -1) {
        k++;
    }
    D_1F800000.view.effect.params[6] = BMagic_Trail[g_Task->unk_04][k].x;
    D_1F800000.view.effect.params[7] = BMagic_Trail[g_Task->unk_04][k].y;
    D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k + 1].x;
    D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k + 1].y;
    D_1F800000.view.effect.params[1] = ratan2(D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5] - D_1F800000.view.effect.params[7]);
    D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k].x;
    D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k].y;
    for (k = k + 1; k < g_Task->timer; k++) {
        D_1F800000.view.effect.params[6] = D_1F800000.view.effect.params[4];
        D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[5];
        D_1F800000.view.effect.params[4] = BMagic_Trail[g_Task->unk_04][k].x;
        D_1F800000.view.effect.params[5] = BMagic_Trail[g_Task->unk_04][k].y;
        prim                             = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] - 0x400) & ANGLE_MASK;
        prim->x0                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y0                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->x2                         = D_1F800000.view.effect.params[6];
        prim->y2                         = D_1F800000.view.effect.params[7];
        D_1F800000.view.effect.params[1] = ratan2(D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5] - D_1F800000.view.effect.params[7]);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] - 0x400) & ANGLE_MASK;
        prim->x1                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y1                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->x3                         = D_1F800000.view.effect.params[4];
        prim->y3                         = D_1F800000.view.effect.params[5];
        D_1F800000.view.effect.params[3] = 129 - (k - 1) * 8;
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[3], 1, D_1F800000.view.effect.params[3]);
        D_1F800000.view.effect.params[3] = 129 - k * 8;
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, D_1F800000.view.effect.params[3], 1, D_1F800000.view.effect.params[3]);
        GFX_AddPrim(3, sizeof(POLY_G4));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
}

/* func_801F02A0 */
#include "overlays/bmagic/Effect_RecordTrail.h"

/* func_801F0390 */
#include "overlays/bmagic/Effect_ClearTrail.h"

MATCH void func_801F0478(void) {
    SYS_DISPATCH_BYTE(D_801F0A2C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F06D8();
    }
}

MATCH void func_801F04F0(void) {
    Battle_ProjectRange();
    g_Task->unk_30.half += 8;
    g_Task->unk_5D = (RANDOM_MASK(3)) + 1;
    g_Task->unk_5E = (RANDOM_MASK(3)) + 1;
    g_Task->unk_5F = (RANDOM_MASK(3)) + 1;
    g_Task->unk_09 = 0;
    g_Task->timer  = 16;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801F05AC);

INCLUDE_ASM(func_801F0638);

/* The textured quad scratch: the corner radius and the colour channels, ahead of the quad corners. */
#define QUAD_RADIUS D_1F800000.view.effect.params[0]
#define QUAD_RED    D_1F800000.view.effect.params[5]
#define QUAD_GREEN  D_1F800000.view.effect.params[6]
#define QUAD_BLUE   D_1F800000.view.effect.params[7]

/* A 32x32 textured quad around the effect position, its corners twice the effect counter (byte 0x09) away,
 * coloured by the timer scaled per channel (bytes 0x5D-0x5F). */
MATCH void func_801F06D8(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 2, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim        = (POLY_FT4*)g_GfxPrimCursor;
    QUAD_RADIUS = g_Task->unk_09 * 2;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->x0 = g_Task->unk_2E.half + FIXED_MUL(rcos(ANGLE_45), QUAD_RADIUS);
    prim->y0 = g_Task->unk_30.half + FIXED_MUL(rsin(ANGLE_45), QUAD_RADIUS);
    prim->x1 = g_Task->unk_2E.half + FIXED_MUL(rcos(1536), QUAD_RADIUS);
    prim->y1 = g_Task->unk_30.half + FIXED_MUL(rsin(1536), QUAD_RADIUS);
    prim->x2 = g_Task->unk_2E.half + FIXED_MUL(rcos(3584), QUAD_RADIUS);
    prim->y2 = g_Task->unk_30.half + FIXED_MUL(rsin(3584), QUAD_RADIUS);
    prim->x3 = g_Task->unk_2E.half + FIXED_MUL(rcos(2560), QUAD_RADIUS);
    prim->y3 = g_Task->unk_30.half + FIXED_MUL(rsin(2560), QUAD_RADIUS);
    setTPage(prim, 0, 2, 832, 256);
    setClut(prim, 32, 506);
    prim->u0   = 128;
    prim->v0   = 32;
    prim->u1   = 160;
    prim->v1   = 32;
    prim->u2   = 128;
    prim->v2   = 64;
    prim->u3   = 160;
    prim->v3   = 64;
    QUAD_RED   = g_Task->timer * (s8)g_Task->unk_5D;
    QUAD_GREEN = g_Task->timer * (s8)g_Task->unk_5E;
    QUAD_BLUE  = g_Task->timer * (s8)g_Task->unk_5F;
    setRGB0(prim, QUAD_RED, QUAD_GREEN, QUAD_BLUE);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}
