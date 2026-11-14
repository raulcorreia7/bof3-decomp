#include "magic093_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

MATCH void func_801EED04(void) {
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u32          i;
    u32          slot;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    func_801F0670();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode++;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            if (!Battle_SlotIsBlocked((u8)(i + 3))) {
                slot                               = Battle_AllocEffect(1, 77) & BYTE_MASK;
                owner                              = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].arg.unk_09   = 16;
                g_BattleEffects[slot].target.party = owner;
                g_Task->unk_09++;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!Battle_SlotIsBlocked((u8)i)) {
                slot                               = Battle_AllocEffect(1, 77) & BYTE_MASK;
                owner                              = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].arg.unk_09   = 16;
                g_BattleEffects[slot].target.party = owner;
                g_Task->unk_09++;
            }
        }
    }
    for (i = 0; i < 8; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        owner                                  = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
        g_Task->param.unk_0B++;
    }
    for (i = 0; i < 16; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        owner                                  = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 1;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 8 + 24;
        BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
        g_Task->param.unk_0B++;
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        *dst++ = *src++ | 0x8000;
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

/* Starts the effect once bytes 0x09 and 0x0B of the work record are both zero. */
MATCH void func_801EF02C(void) {
    u16* flags;

    if ((PARTY_MEMBER_WORD_08(g_Task) & 0xFF00FF00u) == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

/* func_801EF080 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0C4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
}

INCLUDE_ASM(func_801EF108);

MATCH void func_801EF264(void) {
    if (g_BattleEffectBattler->param.unk_0B < 8U) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            Battle_MarkDamaged((g_Task->unk_03 + 3) & BYTE_MASK);
            GFX_FreePaletteFadeTarget(&g_BattleEnemyBattlers[g_Task->unk_03]);
            func_800AF814((g_Task->unk_03 + 3) & BYTE_MASK);
        } else {
            Battle_MarkDamaged(g_Task->unk_03);
            GFX_FreePaletteFadeTarget((EnemyBattler*)&g_Game.members[g_Task->unk_03]);
            func_800AF814(g_Task->unk_03);
        }
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF3A4(void) {
    BATTLE_ACTIVE_WORK->unk_09--;
    func_801E5988();
}

MATCH void func_801EF3D8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 4), 1, g_Task);
}

MATCH void func_801EF41C(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 6), g_Task->header.step);
    g_Task->param.unk_0B += 1;
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF85C();
        func_801EFAE8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF4C8);

INCLUDE_ASM(func_801EF600);

MATCH void func_801EF710(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 8) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF750(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF85C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      red;
    s32      core;
    s32      green;
    s32      blue;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (GetGraphType() == 1 || GetGraphType() == 2) ? 0xA5 : 0x35, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = ((rsin((g_Task->param.unk_0B & 0x1F) << 7) * 16) >> 12) + 0x100;
    red                              = g_Task->unk_09 * 10;
    core                             = g_Task->unk_09 * 9;
    blue                             = g_Task->unk_09 * 2;
    green                            = g_Task->unk_09 * 4;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[1].vz                 = 0;
    D_1F800014[0].vz                 = 0;
    for (i = 1; i <= 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, red, core, blue);
        setRGB1(prim, red, green, blue);
        setRGB2(prim, red, green, blue);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH void func_801EFAE8(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;
    u8       red;
    u8       green;
    u8       blue;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = ((rsin((g_Task->param.unk_0B & 0x1F) << 7) * 16) >> 12) + 0x100;
    D_1F800000.view.effect.params[1] = ((rsin((g_Task->param.unk_0B & 0x1F) << 7) * 16) >> 12) + 0x180;
    red                              = g_Task->unk_09 * 10;
    green                            = g_Task->unk_09 * 4;
    blue                             = g_Task->unk_09 * 2;
    D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
    D_1F800014[3].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vz = D_1F800014[1].vz = D_1F800014[2].vz = D_1F800014[3].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[1]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[1]);
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, red, green, blue);
        setRGB3(prim, red, green, blue);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EFE5C(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801F01F0();
    }
}

MATCH void func_801EFEDC(void) {
    s16* radius;
    u8   count;
    u8   phase;
    u8   pick;
    u8   flags;
    u32  id;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->pos.x.fixed              = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed              = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed              = g_BattleEffectBattler->pos.z.fixed;
        radius                           = &D_1F800000.view.effect.params[0];
        *radius                          = 0x100;
        phase                            = rand() & 7;
        D_1F800000.view.effect.params[5] = phase << 9;
        g_Task->pos.x.fixed += (rsin(phase << 9) * *radius) >> 3;
        g_Task->pos.y.fixed += (rcos(D_1F800000.view.effect.params[5]) * *radius) >> 3;
        flags = g_Task->param.unk_0B;
        if (flags & 1) {
            pick = (flags >> 1) % 3;
            switch (pick) {
                case 0:
                    id = EMI_CUE_ID(SND_BANK_COMMON, 0x01);
                    break;
                case 1:
                    id = EMI_CUE_ID(SND_BANK_COMMON, 0x02);
                    break;
                case 2:
                default:
                    id = EMI_CUE_ID(SND_BANK_COMMON, 0x03);
                    break;
            }
            SND_QueueSelectionEffect(id);
        }
        g_Task->param.unk_0B = 0x10;
        g_Task->unk_09       = 0;
        g_Task->timer        = 0x40;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F00A0(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 32;
    g_Task->unk_09 = timer;
    if (timer == 192) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F00F0(void) {
    PartyMember* work;

    work = g_Task;
    work->unk_09 += 2;
    work = g_Task;
    work->timer--;
    if (work->timer == 48) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F015C(void) {
    u8 ticks;

    g_Task->unk_09 += 1;
    g_Task->timer -= 1;
    ticks                = g_Task->param.unk_0B - 1;
    g_Task->param.unk_0B = ticks;
    if (!(ticks & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

MATCH void func_801F01F0(void) {
    POLY_GT4* prim;
    s32       tpage;
    u8        shade;

    shade                            = g_Task->param.unk_0B * 8;
    D_1F800000.view.effect.params[6] = g_Task->unk_09;
    D_1F800000.view.effect.params[7] = g_Task->timer;
    D_1F800000.view.effect.params[3] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[4] = g_Task->unk_30.half;
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x2A5;
    } else {
        tpage = 0xB5;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));

    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    prim->x0 = D_1F800000.view.effect.params[3] - D_1F800000.view.effect.params[7];
    prim->y0 = D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6];
    prim->x1 = D_1F800000.view.effect.params[3] + D_1F800000.view.effect.params[7];
    prim->y1 = D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6];
    prim->x2 = D_1F800000.view.effect.params[3] - D_1F800000.view.effect.params[7];
    prim->y2 = D_1F800000.view.effect.params[4];
    prim->x3 = D_1F800000.view.effect.params[3] + D_1F800000.view.effect.params[7];
    prim->y3 = D_1F800000.view.effect.params[4];
    setRGB0(prim, shade, shade, shade);
    setRGB1(prim, shade, shade, shade);
    setRGB2(prim, shade, shade, shade);
    setRGB3(prim, shade, shade, shade);
    prim->tpage = GetTPage(1, 1, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUV4(prim, 0x40, 0x40, 0xC0, 0x40, 0x40, 0xFF, 0xC0, 0xFF);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_GT4));

    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    prim->x0 = D_1F800000.view.effect.params[3] - D_1F800000.view.effect.params[7];
    prim->y0 = D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6] - 16;
    prim->x1 = D_1F800000.view.effect.params[3] + D_1F800000.view.effect.params[7];
    prim->y1 = D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6] - 16;
    prim->x2 = D_1F800000.view.effect.params[3] - D_1F800000.view.effect.params[7];
    prim->y2 = D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6];
    prim->x3 = D_1F800000.view.effect.params[3] + D_1F800000.view.effect.params[7];
    prim->y3 = D_1F800000.view.effect.params[4] - D_1F800000.view.effect.params[6];
    setRGB0(prim, 1, 1, 1);
    setRGB1(prim, 1, 1, 1);
    setRGB2(prim, shade, shade, shade);
    setRGB3(prim, shade, shade, shade);
    prim->tpage = GetTPage(1, 1, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUV4(prim, 0x40, 0x30, 0xC0, 0x30, 0x40, 0x40, 0xC0, 0x40);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_GT4));
}

/* func_801F05BC */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0620 */
#include "overlays/bmagic/Actor_Clear.h"

MATCH void func_801F0670(void) {
    s32 count;
    s32 x;
    s32 y;
    s32 z;
    u8  i;

    count = 0;
    z     = 0;
    y     = 0;
    x     = 0;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            if (!Battle_SlotIsBlocked((u8)(i + 3))) {
                count++;
                x += (g_BattleEnemyBattlers[i].pos.x.fixed >> 9) - 0x4000;
                y += (g_BattleEnemyBattlers[i].pos.y.fixed >> 9) - 0x4000;
                z += COORD_INT(g_BattleEnemyBattlers[i].pos.z);
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!Battle_SlotIsBlocked(i)) {
                count++;
                x += (g_Game.members[i].pos.x.fixed >> 9) - 0x4000;
                y += (g_Game.members[i].pos.y.fixed >> 9) - 0x4000;
                z += COORD_INT(g_Game.members[i].pos.z);
            }
        }
    }
    g_Task->pos.x.fixed      = (x / count + 0x4000) << 9;
    g_Task->pos.y.fixed      = (y / count + 0x4000) << 9;
    COORD_INT(g_Task->pos.z) = z / count;
}
