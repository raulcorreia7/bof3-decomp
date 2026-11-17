#include "magic002_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC78(void) {
    u32 index;

    index                                       = Battle_AllocEffect(3, 1) & BYTE_MASK;
    g_BattleEffects[index].header.mode          = 0;
    g_BattleEffects[index].unk_0C               = g_Game.members[0].unk_2E.signed_half << 16;
    g_BattleEffects[index].unk_10               = g_Game.members[0].unk_30.signed_half << 16;
    D_801EC344[index].value                     = 0;
    g_BattleEffects[index].unk_18               = 40;
    g_BattleEffects[index].arg.unk_09           = 0;
    g_BattleEffects[index].unk_1C               = ((g_Battle.selected_actor->unk_2E.signed_half - g_Game.members[0].unk_2E.signed_half) << 16) / 10;
    D_801EC350[index].value                     = ((g_Battle.selected_actor->unk_30.signed_half - g_Game.members[0].unk_30.signed_half) << 16) / 10;
    g_BattleEffects[index].word_60.target_index = 0x100;
    D_801EC388[index].value                     = 0x100;
    D_801EC2E0->target.effect                   = &g_BattleEffects[index];
    g_Task->header.mode += 1;
}

MATCH void func_801EEDE4(void) {
    if (D_801EC2E0->target.party->unk_09 >= 0x28) {
        g_Task->header.mode++;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEE64(void) {
    BMagic_DispatchTaskPair(func_801EEEBC, func_801EEF84);
}

MATCH void func_801EEEBC(void) {
    PartyMember* work;
    PartyMember* draw;

    work = g_Task;
    work->unk_14 += 0x100;
    work->unk_18 += 4;
    work->unk_0C += work->unk_1C;
    work->unk_09++;
    work->unk_10 += work->unk_20;
    draw = g_Task;
    func_801EF1FC(draw->unk_0C >> 16, draw->unk_10 >> 16, (draw->unk_18 << 15) >> 16, draw->unk_14, draw->unk_60, draw->unk_58);
    if (g_Task->unk_09 >= 0xB) {
        g_Task->header.mode++;
    }
}

MATCH void func_801EEF84(void) {
    PartyMember* work;
    PartyMember* draw;

    work = g_Task;
    work->unk_60 += 4;
    work->unk_09++;
    work->unk_58 -= 8;
    work->unk_14 += 0x20;
    draw = g_Task;
    func_801EF1FC(draw->unk_0C >> 16, draw->unk_10 >> 16, (draw->unk_18 << 15) >> 16, draw->unk_14, draw->unk_60, draw->unk_58);
    if (g_Task->unk_09 >= 0x29) {
        Effect_Reset();
    }
}

MATCH void func_801EF030(s32 x, s32 y, u16 radius, s32 phase) {
    SVECTOR  points[6];
    POLY_F3* prim;
    s32      angle;
    u16      tpage;
    u8       i;

    for (i = 0; i < 6; i++) {
        angle        = (i << 12) / 6 + (u16)phase;
        points[i].vx = x + ((rsin(angle) * radius) >> 12);
        points[i].vy = y + ((rcos(angle) * radius) >> 12);
    }
    tpage = GetTPage(0x3C0, 0x100, 0, 0);
    GFX_ADD_DRAW_MODE(tpage);
    for (i = 0; i < 2; i++) {
        prim = (POLY_F3*)g_GfxPrimCursor;
        SetPolyF3(prim);
        setXY3(prim, points[i].vx, points[i].vy, points[i + 2].vx, points[i + 2].vy, points[i + 4].vx, points[i + 4].vy);
        setRGB0(prim, 0xFF, 0xFF, 0);
        SetSemiTrans(prim, 1);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_F3));
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF1FC(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2) {
}
#else
INCLUDE_ASM(func_801EF1FC);
#endif
