#include "magic109_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    RECT         rect;
    PartyMember* work;

    if (g_Battle.target_selector == 0x80 && g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Task->header.mode = 1;
    }
    if (g_Battle.target_selector == 0x40 && !(g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT)) {
        g_Task->header.mode = 1;
    }
    if (g_Task->header.mode != 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->unk_09 = 2;
    work           = g_Task;
    rect.x         = work->unk_2E.half - work->unk_09;
    rect.y         = work->unk_30.half - work->unk_09 + g_FrameBufferIndex * 240;
    rect.h = rect.w = work->unk_09 * 2;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x340, 0x100);
    GFX_AddPrim(3, sizeof(DR_MOVE));
    if (g_Battle.target_selector & 0x40) {
        g_Task->unk_2E.half = D_801EF9D8[g_Battle.scroll_dir].x;
        g_Task->unk_30.half = D_801EF9D8[g_Battle.scroll_dir].y;
    } else {
        g_Task->unk_2E.half = D_801EF9D8[g_Battle.scroll_dir ^ 2].x;
        g_Task->unk_30.half = D_801EF9D8[g_Battle.scroll_dir ^ 2].y;
    }
    g_Task->unk_64 = 0;
    g_Task->header.mode += 1;
}

MATCH void func_801EEEAC(void) {
    u8 count;

    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x54) {
        g_Task->header.mode += 1;
        g_Task->timer = 64;
    }
    func_801EF0F8(g_Task->unk_64);
}

MATCH void func_801EEF30(void) {
    s32 raised_offset;
    s32 lowered_offset;
    u8  timer;

    timer         = g_Task->timer;
    g_Task->timer = timer + 0xFF;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->header.mode += 1;
    }
    func_801EF0F8(g_Task->unk_64);
    if (g_Task->param.unk_0B == 0) {
        raised_offset  = g_Task->unk_64 + 8;
        g_Task->unk_64 = raised_offset;
        if (raised_offset >= 0x80) {
            g_Task->param.unk_0B = 1;
        }
    } else {
        lowered_offset = g_Task->unk_64 - 8;
        g_Task->unk_64 = lowered_offset;
        if (lowered_offset < -0x7F) {
            g_Task->param.unk_0B = 0;
        }
    }
}

MATCH void func_801EF008(void) {
    u8  timer;
    s32 offset;

    timer          = g_Task->unk_09 - 2;
    g_Task->unk_09 = timer;
    if (timer == 2) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    func_801EF0F8(g_Task->unk_64);
    if (g_Task->param.unk_0B == 0) {
        offset         = g_Task->unk_64 + 8;
        g_Task->unk_64 = offset;
        if (offset >= 0x80) {
            g_Task->param.unk_0B = 1;
        }
    } else {
        offset         = g_Task->unk_64 - 8;
        g_Task->unk_64 = offset;
        if (offset < -0x7F) {
            g_Task->param.unk_0B = 0;
        }
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF0F8(s32 offset) {
    extern u8    D_801EF9F8[];
    extern u8    D_801EF9FC[];
    extern u8    D_801EFA78[];
    extern u8    D_801EFA7C[];
    extern u8    D_801EFAF8[];
    extern u8    D_801EFAFC[];
    s16          sp18;
    s16          sp1A;
    s16          sp1C;
    s16          sp1E;
    s32          sp20;
    s32          sp28;
    s32          sp30;
    u8*          var_s2;
    u8*          var_s4;
    s16          temp_v0_10;
    s16          temp_v0_11;
    s16          temp_v0_12;
    s16          temp_v0_13;
    s16          temp_v0_14;
    s16          temp_v0_15;
    s16          temp_v0_16;
    s16          temp_v0_17;
    s16          temp_v0_18;
    s16          temp_v0_19;
    s16          temp_v0_20;
    s16          temp_v0_21;
    s16          temp_v0_22;
    s16          temp_v0_23;
    s16          temp_v0_24;
    s16          temp_v0_3;
    s16          temp_v0_9;
    s16          var_v1_2;
    s32          temp_a0;
    s32          temp_a0_2;
    s32          temp_a0_3;
    s32          temp_a0_4;
    s32          temp_a1;
    s32          temp_a1_2;
    s32          temp_a1_3;
    s32          temp_a1_4;
    s32          temp_a2;
    s32          temp_a2_2;
    s32          temp_a2_3;
    s32          temp_a2_4;
    s32          temp_s0;
    s32          temp_s0_2;
    s32          temp_s0_3;
    s32          temp_s0_4;
    s32          temp_s1;
    s32          temp_s1_2;
    s32          temp_s1_3;
    s32          temp_s1_4;
    s32          temp_s6;
    s32          temp_s7;
    s32          temp_t1;
    s32          temp_v0_26;
    s32          temp_v1;
    s32          temp_v1_2;
    s32          temp_v1_3;
    s32          temp_v1_4;
    s32          temp_v1_5;
    s32          var_a3;
    s32          var_s0;
    s32          var_s1;
    s32          var_v0;
    s32          var_v1;
    s8           temp_v0;
    s8           temp_v0_25;
    s8           temp_v0_28;
    s8           temp_v0_2;
    s8           temp_v0_4;
    s8           temp_v0_5;
    s8           temp_v0_6;
    s8           temp_v0_7;
    s8           temp_v0_8;
    s8           var_s3;
    s8           var_s3_2;
    s8           var_s3_3;
    s8           var_s3_4;
    s8           var_s5;
    s8           var_s5_2;
    s8           var_s5_3;
    POLY_GT4*    temp_s0_5;
    POLY_F4*     temp_s1_5;
    PartyMember* temp_a3;
    PartyMember* temp_t0;
    u8*          temp_v0_27;
    u8*          temp_v1_6;

    var_s5 = 0;
    sp20   = offset;
    sp28   = 0;
    do {
        var_s3 = 0;
    loop_2:
        temp_s1                           = var_s3 << 8;
        temp_s0                           = (var_s3 * 8) + (var_s5 << 7);
        (*((s32*)(D_801EFAF8 + temp_s0))) = (s32)(rsin(temp_s1) * var_s5 * ((u8)(g_Task)->unk_09 >> 3)) >> 0xC;
        temp_t0                           = g_Task;
        temp_v0_2                         = var_s3 + 1;
        var_s3                            = temp_v0_2;
        (*((s32*)(D_801EFAFC + temp_s0))) = (s32)(rcos(temp_s1) * var_s5 * ((u8)temp_t0->unk_09 >> 3)) >> 0xC;
        temp_v0                           = var_s5 + 1;
        if (temp_v0_2 < 0x10) {
            goto loop_2;
        }
        var_s5 = temp_v0;
    } while (temp_v0 < 9);
    sp18      = temp_t0->unk_2E.half - temp_t0->unk_09;
    sp1A      = (temp_t0->unk_30.half - temp_t0->unk_09) + (g_FrameBufferIndex * 0xF0);
    temp_v0_3 = temp_t0->unk_09 * 2;
    sp1C      = temp_v0_3;
    sp1E      = temp_v0_3;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, (RECT*)&sp18, 0x340, 0x100);
    GFX_AddPrim(3U, 0x18U);
    var_a3 = 0x42D;
    if (GetGraphType() != 1) {
        var_a3 = 0x11D;
        if (GetGraphType() == 2) {
            var_a3 = 0x42D;
        }
    }
    var_s5_2 = 0;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, var_a3, NULL);
    GFX_AddPrim(3U, 0xCU);
    var_s0 = 0 << 0x18;
    do {
        temp_s0_2                           = var_s0 >> 0x18;
        temp_s1_2                           = temp_s0_2 << 8;
        temp_s0_3                           = temp_s0_2 * 8;
        (*((s32*)(D_801EF9F8 + temp_s0_3))) = (s32)(rsin(temp_s1_2) * (g_Task)->unk_09) >> 0xC;
        temp_v0_4                           = var_s5_2 + 1;
        var_s5_2                            = temp_v0_4;
        (*((s32*)(D_801EF9FC + temp_s0_3))) = (s32)(rcos(temp_s1_2) * (g_Task)->unk_09) >> 0xC;
        var_s0                              = var_s5_2 << 0x18;
    } while (temp_v0_4 < 0x10);
    var_s5_3 = 7;
    var_v1   = 7 << 0x18;
    do {
        temp_v1  = var_v1 >> 0x18;
        var_s3_2 = 0;
        sp28 += sp20 * (8 - temp_v1);
        var_s1 = 0 << 0x18;
    loop_11:
        temp_s1_3                           = var_s1 >> 0x18;
        temp_s0_4                           = sp28 + (temp_s1_3 << 8);
        temp_s1_4                           = temp_s1_3 * 8;
        (*((s32*)(D_801EFA78 + temp_s1_4))) = (s32)(rsin(temp_s0_4) * temp_v1 * ((u8)(g_Task)->unk_09 >> 3)) >> 0xC;
        temp_v0_6                           = var_s3_2 + 1;
        var_s3_2                            = temp_v0_6;
        (*((s32*)(D_801EFA7C + temp_s1_4))) = (s32)(rcos(temp_s0_4) * temp_v1 * ((u8)(g_Task)->unk_09 >> 3)) >> 0xC;
        var_s1                              = var_s3_2 << 0x18;
        if (temp_v0_6 < 0x10) {
            goto loop_11;
        }
        var_s4   = D_801EF9F8;
        var_s2   = D_801EFA78;
        var_s3_3 = 0;
        temp_t1  = var_s5_3 + 1;
        sp30     = temp_t1;
        temp_s7  = temp_t1 << 7;
        temp_s6  = var_s5_3 << 7;
    loop_13:
        temp_s1_5 = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4((POLY_F4*)temp_s1_5);
        temp_s1_5->r0 = 0;
        temp_s1_5->g0 = 0;
        temp_s1_5->b0 = 0;
        temp_s0_5     = (POLY_GT4*)(g_GfxPrimCursor + 0x18);
        SetPolyGT4((POLY_GT4*)temp_s0_5);
        var_v1_2 = 0x42D;
        if (GetGraphType() != 1) {
            var_v1_2 = 0x11D;
            if (GetGraphType() == 2) {
                var_v1_2 = 0x42D;
            }
        }
        temp_v0_7        = sp30 * 0x10;
        temp_s0_5->r0    = temp_v0_7;
        temp_s0_5->g0    = temp_v0_7;
        temp_s0_5->b0    = temp_v0_7;
        temp_s0_5->r1    = temp_v0_7;
        temp_s0_5->g1    = temp_v0_7;
        temp_s0_5->b1    = temp_v0_7;
        temp_v0_8        = var_s5_3 * 0x10;
        temp_s0_5->r2    = temp_v0_8;
        temp_s0_5->g2    = temp_v0_8;
        temp_s0_5->b2    = temp_v0_8;
        temp_s0_5->r3    = temp_v0_8;
        temp_s0_5->g3    = temp_v0_8;
        temp_s0_5->b3    = temp_v0_8;
        temp_a3          = g_Task;
        temp_s0_5->tpage = var_v1_2;
        if (temp_a3->unk_64 > 0) {
            temp_a2       = ((var_s3_3 + 1) & 0xF) * 8;
            temp_v0_9     = temp_a3->unk_2E.half + (*(s32*)var_s4);
            temp_s0_5->x0 = temp_v0_9;
            temp_s1_5->x0 = temp_v0_9;
            temp_v1_2     = (*(s32*)(var_s4 + 4));
            var_s4        = D_801EF9F8 + temp_a2;
            temp_v0_10    = temp_a3->unk_30.half + temp_v1_2;
            temp_s0_5->y0 = temp_v0_10;
            temp_s1_5->y0 = temp_v0_10;
            temp_v0_11    = temp_a3->unk_2E.half + (*(s32*)var_s4);
            temp_s0_5->x1 = temp_v0_11;
            temp_s1_5->x1 = temp_v0_11;
            temp_v0_12    = temp_a3->unk_30.half + (*(s32*)(var_s4 + 4));
            temp_s0_5->y1 = temp_v0_12;
            temp_s1_5->y1 = temp_v0_12;
            temp_v0_13    = temp_a3->unk_2E.half + (*(s32*)var_s2);
            temp_s0_5->x2 = temp_v0_13;
            temp_s1_5->x2 = temp_v0_13;
            temp_v1_3     = (*(s32*)(var_s2 + 4));
            var_s2        = D_801EFA78 + temp_a2;
            temp_v0_14    = temp_a3->unk_30.half + temp_v1_3;
            temp_s0_5->y2 = temp_v0_14;
            temp_s1_5->y2 = temp_v0_14;
            temp_a1       = (var_s3_3 & 0xF) * 8;
            temp_v0_15    = temp_a3->unk_2E.half + (*(s32*)var_s2);
            temp_s0_5->x3 = temp_v0_15;
            temp_s1_5->x3 = temp_v0_15;
            temp_a0       = temp_a1 + temp_s7;
            temp_v0_16    = temp_a3->unk_30.half + (*(s32*)(var_s2 + 4));
            temp_s0_5->y3 = temp_v0_16;
            temp_s1_5->y3 = temp_v0_16;
            temp_s0_5->u0 = (s8)(temp_a3->unk_09 + (*((s32*)(D_801EFAF8 + temp_a0))));
            temp_a0_2     = temp_a2 + temp_s7;
            temp_s0_5->v0 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAFC + temp_a0))));
            temp_s0_5->u1 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAF8 + temp_a0_2))));
            temp_a1_2     = temp_a1 + temp_s6;
            temp_s0_5->v1 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAFC + temp_a0_2))));
            temp_s0_5->u2 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAF8 + temp_a1_2))));
            temp_a2_2     = temp_a2 + temp_s6;
            temp_s0_5->v2 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAFC + temp_a1_2))));
            temp_s0_5->u3 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAF8 + temp_a2_2))));
            temp_s0_5->v3 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAFC + temp_a2_2))));
        } else {
            temp_a2_3     = ((var_s3_3 + 1) & 0xF) * 8;
            temp_v0_17    = temp_a3->unk_2E.half + (*(s32*)var_s4);
            temp_s0_5->x1 = temp_v0_17;
            temp_s1_5->x1 = temp_v0_17;
            temp_v1_4     = (*(s32*)(var_s4 + 4));
            var_s4        = D_801EF9F8 + temp_a2_3;
            temp_v0_18    = temp_a3->unk_30.half + temp_v1_4;
            temp_s0_5->y1 = temp_v0_18;
            temp_s1_5->y1 = temp_v0_18;
            temp_v0_19    = temp_a3->unk_2E.half + (*(s32*)var_s4);
            temp_s0_5->x0 = temp_v0_19;
            temp_s1_5->x0 = temp_v0_19;
            temp_v0_20    = temp_a3->unk_30.half + (*(s32*)(var_s4 + 4));
            temp_s0_5->y0 = temp_v0_20;
            temp_s1_5->y0 = temp_v0_20;
            temp_v0_21    = temp_a3->unk_2E.half + (*(s32*)var_s2);
            temp_s0_5->x3 = temp_v0_21;
            temp_s1_5->x3 = temp_v0_21;
            temp_v1_5     = (*(s32*)(var_s2 + 4));
            var_s2        = D_801EFA78 + temp_a2_3;
            temp_v0_22    = temp_a3->unk_30.half + temp_v1_5;
            temp_s0_5->y3 = temp_v0_22;
            temp_s1_5->y3 = temp_v0_22;
            temp_a1_3     = (var_s3_3 & 0xF) * 8;
            temp_v0_23    = temp_a3->unk_2E.half + (*(s32*)var_s2);
            temp_s0_5->x2 = temp_v0_23;
            temp_s1_5->x2 = temp_v0_23;
            temp_a0_3     = temp_a1_3 + temp_s7;
            temp_v0_24    = temp_a3->unk_30.half + (*(s32*)(var_s2 + 4));
            temp_s0_5->y2 = temp_v0_24;
            temp_s1_5->y2 = temp_v0_24;
            temp_s0_5->u1 = (s8)(temp_a3->unk_09 + (*((s32*)(D_801EFAF8 + temp_a0_3))));
            temp_a0_4     = temp_a2_3 + temp_s7;
            temp_s0_5->v1 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAFC + temp_a0_3))));
            temp_s0_5->u0 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAF8 + temp_a0_4))));
            temp_a1_4     = temp_a1_3 + temp_s6;
            temp_s0_5->v0 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAFC + temp_a0_4))));
            temp_s0_5->u3 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAF8 + temp_a1_4))));
            temp_a2_4     = temp_a2_3 + temp_s6;
            temp_s0_5->v3 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAFC + temp_a1_4))));
            temp_s0_5->u2 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAF8 + temp_a2_4))));
            temp_s0_5->v2 = (s8)((g_Task)->unk_09 + (*((s32*)(D_801EFAFC + temp_a2_4))));
        }
        GFX_AddPrim(3U, 0x18U);
        GFX_AddPrim(3U, 0x34U);
        temp_v0_25 = var_s3_3 + 1;
        var_s3_3   = temp_v0_25;
        if (temp_v0_25 < 0x10) {
            goto loop_13;
        }
        var_s3_4 = 0;
        var_v0   = 0 << 0x18;
    loop_21:
        temp_v0_26               = var_v0 >> 0x15;
        temp_v1_6                = D_801EF9F8 + temp_v0_26;
        temp_v0_27               = D_801EFA78 + (temp_v0_26 >> 2);
        (*(s32*)temp_v1_6)       = (s32)(*(s32*)temp_v0_27);
        (*(s32*)(temp_v1_6 + 4)) = (s32)(*(s32*)(temp_v0_27 + 4));
        temp_v0_28               = var_s3_4 + 1;
        var_s3_4                 = temp_v0_28;
        var_v0                   = var_s3_4 << 0x18;
        if (temp_v0_28 < 0x10) {
            goto loop_21;
        }
        temp_v0_5 = var_s5_3 - 1;
        var_s5_3  = temp_v0_5;
        var_v1    = var_s5_3 << 0x18;
    } while (!(temp_v0_5 & 0x80));
}
#else
INCLUDE_ASM(func_801EF0F8);
#endif
