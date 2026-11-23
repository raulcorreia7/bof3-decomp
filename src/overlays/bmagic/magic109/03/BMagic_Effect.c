#include "magic109_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    RECT         rect;
    PartyMember* work;

    if (g_Battle.target_selector == 0x80 && g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        TASK(PartyMember)->header.mode = 1;
    }
    if (g_Battle.target_selector == 0x40 && !(g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT)) {
        TASK(PartyMember)->header.mode = 1;
    }
    if (TASK(PartyMember)->header.mode != 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
        return;
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    TASK(PartyMember)->unk_09 = 2;
    work                      = TASK(PartyMember);
    rect.x                    = work->screen_x.value - work->unk_09;
    rect.y                    = work->screen_y.value - work->unk_09 + g_GfxBufferIndex * 240;
    rect.h = rect.w = work->unk_09 * 2;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x340, 0x100);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MOVE));
    if (g_Battle.target_selector & 0x40) {
        TASK(PartyMember)->screen_x.value = D_801EF9D8[g_Battle.scroll_dir].x;
        TASK(PartyMember)->screen_y.value = D_801EF9D8[g_Battle.scroll_dir].y;
    } else {
        TASK(PartyMember)->screen_x.value = D_801EF9D8[g_Battle.scroll_dir ^ 2].x;
        TASK(PartyMember)->screen_y.value = D_801EF9D8[g_Battle.scroll_dir ^ 2].y;
    }
    TASK(PartyMember)->unk_64 = 0;
    TASK(PartyMember)->header.mode += 1;
}

MATCH void func_801EEEAC(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 + 2;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x54) {
        TASK(PartyMember)->header.mode += 1;
        TASK(PartyMember)->timer = 64;
    }
    func_801EF0F8(TASK(PartyMember)->unk_64);
}

MATCH void func_801EEF30(void) {
    s32 raised_offset;
    s32 lowered_offset;
    u8  timer;

    timer                    = TASK(PartyMember)->timer;
    TASK(PartyMember)->timer = timer + 0xFF;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        TASK(PartyMember)->header.mode += 1;
    }
    func_801EF0F8(TASK(PartyMember)->unk_64);
    if (TASK(PartyMember)->param.unk_0B == 0) {
        raised_offset             = TASK(PartyMember)->unk_64 + 8;
        TASK(PartyMember)->unk_64 = raised_offset;
        if (raised_offset >= 0x80) {
            TASK(PartyMember)->param.unk_0B = 1;
        }
    } else {
        lowered_offset            = TASK(PartyMember)->unk_64 - 8;
        TASK(PartyMember)->unk_64 = lowered_offset;
        if (lowered_offset < -0x7F) {
            TASK(PartyMember)->param.unk_0B = 0;
        }
    }
}

MATCH void func_801EF008(void) {
    u8  timer;
    s32 offset;

    timer                     = TASK(PartyMember)->unk_09 - 2;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 2) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
        return;
    }
    func_801EF0F8(TASK(PartyMember)->unk_64);
    if (TASK(PartyMember)->param.unk_0B == 0) {
        offset                    = TASK(PartyMember)->unk_64 + 8;
        TASK(PartyMember)->unk_64 = offset;
        if (offset >= 0x80) {
            TASK(PartyMember)->param.unk_0B = 1;
        }
    } else {
        offset                    = TASK(PartyMember)->unk_64 - 8;
        TASK(PartyMember)->unk_64 = offset;
        if (offset < -0x7F) {
            TASK(PartyMember)->param.unk_0B = 0;
        }
    }
}

/* Draws the swirl: a 9-ring mesh of texture points, then eight rings of 16 Gouraud quads, each
 * ring twisted by offset times its depth, the quads mirrored when unk_64 is not positive. */
MATCH void func_801EF0F8(s32 offset) {
    RECT      move;
    s32       ring_angle;
    s8        ring;
    s8        segment;
    Offset2*  rim;
    Offset2*  spiral;
    POLY_F4*  shadow;
    POLY_GT4* quad;

    ring_angle = 0;
    for (ring = 0; ring < 9; ring++) {
        for (segment = 0; segment < 16; segment++) {
            D_801EFAF8[ring][segment].x = (rsin(segment << 8) * ring * (TASK(PartyMember)->unk_09 >> 3)) >> 12;
            D_801EFAF8[ring][segment].y = (rcos(segment << 8) * ring * (TASK(PartyMember)->unk_09 >> 3)) >> 12;
        }
    }
    move.x = TASK(PartyMember)->screen_x.value - TASK(PartyMember)->unk_09;
    move.y = TASK(PartyMember)->screen_y.value - TASK(PartyMember)->unk_09 + g_GfxBufferIndex * SCREEN_HEIGHT;
    move.h = move.w = TASK(PartyMember)->unk_09 * 2;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &move, 832, 256);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MOVE));
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 832, 256));
    for (ring = 0; ring < 16; ring++) {
        D_801EF9F8[ring].x = FIXED_MUL(rsin(ring << 8), TASK(PartyMember)->unk_09);
        D_801EF9F8[ring].y = FIXED_MUL(rcos(ring << 8), TASK(PartyMember)->unk_09);
    }
    for (ring = 7; ring >= 0; ring--) {
        ring_angle += offset * (8 - ring);
        for (segment = 0; segment < 16; segment++) {
            D_801EFA78[segment].x = (rsin(ring_angle + (segment << 8)) * ring * (TASK(PartyMember)->unk_09 >> 3)) >> 12;
            D_801EFA78[segment].y = (rcos(ring_angle + (segment << 8)) * ring * (TASK(PartyMember)->unk_09 >> 3)) >> 12;
        }
        rim    = D_801EF9F8;
        spiral = D_801EFA78;
        for (segment = 0; segment < 16; segment++) {
            shadow = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(shadow);
            setRGB0(shadow, 0, 0, 0);
            quad = (POLY_GT4*)(g_GfxPrimCursor + sizeof(POLY_F4));
            SetPolyGT4(quad);
            quad->tpage = getTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 832, 256);
            setRGB0(quad, (ring + 1) * 16, (ring + 1) * 16, (ring + 1) * 16);
            setRGB1(quad, (ring + 1) * 16, (ring + 1) * 16, (ring + 1) * 16);
            setRGB2(quad, ring * 16, ring * 16, ring * 16);
            setRGB3(quad, ring * 16, ring * 16, ring * 16);
            if (TASK(PartyMember)->unk_64 > 0) {
                shadow->x0 = quad->x0 = TASK(PartyMember)->screen_x.value + rim->x;
                shadow->y0 = quad->y0 = TASK(PartyMember)->screen_y.value + rim->y;
                rim                   = &D_801EF9F8[(segment + 1) & 0xF];
                shadow->x1 = quad->x1 = TASK(PartyMember)->screen_x.value + rim->x;
                shadow->y1 = quad->y1 = TASK(PartyMember)->screen_y.value + rim->y;
                shadow->x2 = quad->x2 = TASK(PartyMember)->screen_x.value + spiral->x;
                shadow->y2 = quad->y2 = TASK(PartyMember)->screen_y.value + spiral->y;
                spiral                = &D_801EFA78[(segment + 1) & 0xF];
                shadow->x3 = quad->x3 = TASK(PartyMember)->screen_x.value + spiral->x;
                shadow->y3 = quad->y3 = TASK(PartyMember)->screen_y.value + spiral->y;
                setUV4(quad, TASK(PartyMember)->unk_09 + D_801EFAF8[ring + 1][segment & 0xF].x, TASK(PartyMember)->unk_09 + D_801EFAF8[ring + 1][segment & 0xF].y,
                       TASK(PartyMember)->unk_09 + D_801EFAF8[ring + 1][(segment + 1) & 0xF].x, TASK(PartyMember)->unk_09 + D_801EFAF8[ring + 1][(segment + 1) & 0xF].y,
                       TASK(PartyMember)->unk_09 + D_801EFAF8[ring][segment & 0xF].x, TASK(PartyMember)->unk_09 + D_801EFAF8[ring][segment & 0xF].y,
                       TASK(PartyMember)->unk_09 + D_801EFAF8[ring][(segment + 1) & 0xF].x, TASK(PartyMember)->unk_09 + D_801EFAF8[ring][(segment + 1) & 0xF].y);
            } else {
                shadow->x1 = quad->x1 = TASK(PartyMember)->screen_x.value + rim->x;
                shadow->y1 = quad->y1 = TASK(PartyMember)->screen_y.value + rim->y;
                rim                   = &D_801EF9F8[(segment + 1) & 0xF];
                shadow->x0 = quad->x0 = TASK(PartyMember)->screen_x.value + rim->x;
                shadow->y0 = quad->y0 = TASK(PartyMember)->screen_y.value + rim->y;
                shadow->x3 = quad->x3 = TASK(PartyMember)->screen_x.value + spiral->x;
                shadow->y3 = quad->y3 = TASK(PartyMember)->screen_y.value + spiral->y;
                spiral                = &D_801EFA78[(segment + 1) & 0xF];
                shadow->x2 = quad->x2 = TASK(PartyMember)->screen_x.value + spiral->x;
                shadow->y2 = quad->y2 = TASK(PartyMember)->screen_y.value + spiral->y;
                quad->u1              = TASK(PartyMember)->unk_09 + D_801EFAF8[ring + 1][segment & 0xF].x;
                quad->v1              = TASK(PartyMember)->unk_09 + D_801EFAF8[ring + 1][segment & 0xF].y;
                quad->u0              = TASK(PartyMember)->unk_09 + D_801EFAF8[ring + 1][(segment + 1) & 0xF].x;
                quad->v0              = TASK(PartyMember)->unk_09 + D_801EFAF8[ring + 1][(segment + 1) & 0xF].y;
                quad->u3              = TASK(PartyMember)->unk_09 + D_801EFAF8[ring][segment & 0xF].x;
                quad->v3              = TASK(PartyMember)->unk_09 + D_801EFAF8[ring][segment & 0xF].y;
                quad->u2              = TASK(PartyMember)->unk_09 + D_801EFAF8[ring][(segment + 1) & 0xF].x;
                quad->v2              = TASK(PartyMember)->unk_09 + D_801EFAF8[ring][(segment + 1) & 0xF].y;
            }
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_F4));
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
        }
        for (segment = 0; segment < 16; segment++) {
            D_801EF9F8[segment] = D_801EFA78[segment];
        }
    }
}
