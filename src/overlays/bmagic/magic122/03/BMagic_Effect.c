#include "magic122_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDFC};
    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* battler;
    PartyMember* task;
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u16*         dst2;
    u16*         src2;
    u16*         dst3;
    u16*         src3;
    u32          slot;
    u32          i;

    g_Task->facing = g_BattleEffectBattler->facing;
    battler        = g_BattleEffectBattler;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &battler->pos);
    slot                               = Battle_AllocEffect(1, 56) & BYTE_MASK;
    owner                              = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 4;
    g_BattleEffects[slot].target.party = owner;
    i                                  = 1;
    dst                                = &MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[1];
    src                                = &MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW)[1];
    for (; i < 16; i++) {
        *dst++ = *src++ | 0x8000;
    }
    i    = 1;
    src2 = &MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW)[1];
    dst2 = &MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[1];
    for (; i < 16; i++) {
        dst2[16] = src2[16];
        dst2++;
        src2++;
    }
    i    = 1;
    src3 = &MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW)[1];
    dst3 = &MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[1];
    for (; i < 16; i++) {
        dst3[32] = src3[32] | 0x8000;
        dst3++;
        src3++;
    }
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[0]  = 0;
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[16] = 0;
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[32] = 0;
    g_GfxPalettePending                                         = 1;
    g_Task->param.unk_0B                                        = 0;
    g_Task->unk_09                                              = 0;
    g_Task->header.mode++;
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

/* func_801EEE5C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEA0(void) {
    SYS_DISPATCH_BYTE(D_801F02D0, g_Task->header.step);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        if (g_Task->header.step != 0) {
            func_801EFBA8();
            func_801EF324();
        }
    }
}

MATCH void func_801EEF2C(void) {
    PartyMember* battler;
    PartyMember* work;

    if (--g_Task->unk_09 == 0) {
        g_Task->facing = g_BattleEffectBattler->facing;
        Battle_CenterCamera();
        Battle_ProjectRange();
        work                             = g_Task;
        battler                          = g_BattleEffectBattler;
        D_1F800000.view.effect.params[6] = work->unk_2E.half;
        D_1F800000.view.effect.params[7] = work->unk_30.half;
        WorldPos_Copy(&work->pos, &battler->pos);
        Battle_ProjectRange();
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            func_800B0118();
        } else {
            switch (g_Task->facing) {
                case 0:
                    g_Task->unk_0C = 41;
                    g_Task->unk_10 = -13;
                    break;
                case 1:
                    g_Task->unk_0C = -41;
                    g_Task->unk_10 = -13;
                    break;
                case 2:
                    g_Task->unk_0C = -38;
                    g_Task->unk_10 = -38;
                    break;
                default:
                    g_Task->unk_0C = 38;
                    g_Task->unk_10 = -38;
                    break;
            }
        }
        g_Task->unk_2E.half += g_Task->unk_0C;
        g_Task->unk_30.half += g_Task->unk_10;
        D_1F800000.view.effect.params[4] = g_Task->unk_2E.half;
        D_1F800000.view.effect.params[5] = g_Task->unk_30.half;
        g_Task->unk_14                   = ratan2(D_1F800000.view.effect.params[6] - D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[7] - D_1F800000.view.effect.params[5]);
        g_Task->unk_04                   = 16;
        g_Task->param.unk_0B             = 17;
        g_Task->unk_09                   = 0;
        g_Task->timer                    = 1;
        g_Task->header.step++;
        SND_QueueSelectionFx(0x100);
    }
}

MATCH void func_801EF158(void) {
    PartyMember* work;

    work = g_Task;
    work->timer += 3;
    work = g_Task;
    work->unk_09++;
    if (work->unk_09 == 8) {
        work = g_Task;
        work->header.step++;
    }
}

#include "overlays/bmagic/Effect_CountUpTimerCallSelector.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt120.h"

#include "overlays/bmagic/Effect_CountUpAndFinishAt136.h"

MATCH void func_801EF324(void) {
    POLY_GT4* prim;
    s32       tpage;
    s32       i;
    s32       inner;
    s32       outer;
    s32       swing;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    GFX_AddDitheredDrawMode(3, tpage);
    D_1F800000.view.effect.params[4] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[5] = g_Task->unk_30.half;
    D_1F800000.view.effect.params[1] = g_Task->unk_14;
    for (i = 1; i < g_Task->timer + 1; i++) {
        D_1F800000.view.effect.params[6] = D_1F800000.view.effect.params[4];
        D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[5];
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] + FIXED_MUL(rsin(((i + g_Task->unk_09) & 0x3F) << 6), 0x100)) & ANGLE_MASK;
        D_1F800000.view.effect.params[4] += FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), 16);
        D_1F800000.view.effect.params[5] += FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), 16);
        prim  = (POLY_GT4*)g_GfxPrimCursor;
        inner = ((i - 1 - g_Task->unk_09) & 0x3F) << 6;
        outer = ((i - g_Task->unk_09) & 0x3F) << 6;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] + 0x400) & ANGLE_MASK;
        swing                            = FIXED_MUL(rsin(inner), 2) + 4;
        D_1F800000.view.effect.params[0] = (i - 1) * 9 + swing;
        D_1F800000.view.effect.params[0] = D_1F800000.view.effect.params[0] / g_Task->param.unk_0B + 1;
        prim->x1                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y1                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        swing                            = FIXED_MUL(rsin(outer), 2) + 4;
        D_1F800000.view.effect.params[0] = i * 9 + swing;
        D_1F800000.view.effect.params[0] = D_1F800000.view.effect.params[0] / g_Task->param.unk_0B + 1;
        prim->x3                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y3                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->x0                         = D_1F800000.view.effect.params[6];
        prim->y0                         = D_1F800000.view.effect.params[7];
        prim->x2                         = D_1F800000.view.effect.params[4];
        prim->y2                         = D_1F800000.view.effect.params[5];
        prim->clut                       = GetClut(0, 0x1FA);
        prim->tpage                      = GetTPage(0, 1, 0x380, 0x100);
        prim->u0                         = 0x40;
        prim->v0                         = i * 8 - g_Task->unk_09 * 16;
        prim->u1                         = 0x80;
        prim->v1                         = i * 8 - g_Task->unk_09 * 16;
        prim->u2                         = 0x40;
        prim->v2                         = i * 8 - g_Task->unk_09 * 16 + 8;
        prim->u3                         = 0x80;
        prim->v3                         = i * 8 - g_Task->unk_09 * 16 + 8;
        D_1F800000.view.effect.params[3] = g_Task->unk_04 * 8;
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        D_1F800000.view.effect.params[3] = g_Task->unk_04;
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        GFX_AddPrim(3, sizeof(POLY_GT4));
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[1] - 0x400) & ANGLE_MASK;
        swing                            = FIXED_MUL(rsin(inner), 2) + 4;
        D_1F800000.view.effect.params[0] = (i - 1) * 9 + swing;
        D_1F800000.view.effect.params[0] = D_1F800000.view.effect.params[0] / g_Task->param.unk_0B + 1;
        prim->x0                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y0                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        swing                            = FIXED_MUL(rsin(outer), 2) + 4;
        D_1F800000.view.effect.params[0] = i * 9 + swing;
        D_1F800000.view.effect.params[0] = D_1F800000.view.effect.params[0] / g_Task->param.unk_0B + 1;
        prim->x2                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y2                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->x1                         = D_1F800000.view.effect.params[6];
        prim->y1                         = D_1F800000.view.effect.params[7];
        prim->x3                         = D_1F800000.view.effect.params[4];
        prim->y3                         = D_1F800000.view.effect.params[5];
        prim->clut                       = GetClut(0, 0x1FA);
        prim->tpage                      = GetTPage(0, 1, 0x380, 0x100);
        prim->u0                         = 0;
        prim->v0                         = i * 8 - g_Task->unk_09 * 16;
        prim->u1                         = 0x40;
        prim->v1                         = i * 8 - g_Task->unk_09 * 16;
        prim->u2                         = 0;
        prim->v2                         = i * 8 - g_Task->unk_09 * 16 + 8;
        prim->u3                         = 0x40;
        prim->v3                         = i * 8 - g_Task->unk_09 * 16 + 8;
        D_1F800000.view.effect.params[3] = g_Task->unk_04 * 8;
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        D_1F800000.view.effect.params[3] = g_Task->unk_04;
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        GFX_AddPrim(3, sizeof(POLY_GT4));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    GFX_AddDitheredDrawMode(3, tpage);
}

INCLUDE_ASM(func_801EFBA8);
