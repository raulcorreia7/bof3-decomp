#include "magic109_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC14.h"

/* func_801EEC80 */
MATCH void BMagic_SwirlStart(void) {
    RECT          rect;
    Magic109Task* work;

    if (g_Battle.target_selector == 0x80 && g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        TASK(Magic109Task)->header.mode = 1;
    }
    if (g_Battle.target_selector == 0x40 && !(g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT)) {
        TASK(Magic109Task)->header.mode = 1;
    }
    if (TASK(Magic109Task)->header.mode != 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
        return;
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    TASK(Magic109Task)->radius = BMAGIC_SWIRL_RADIUS_START;
    work                       = TASK(Magic109Task);
    rect.x                     = work->screen_x.value - work->radius;
    rect.y                     = work->screen_y.value - work->radius + g_GfxBufferIndex * SCREEN_HEIGHT;
    rect.h = rect.w = work->radius * 2;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, BMAGIC_SWIRL_TEXTURE_X, BMAGIC_SWIRL_TEXTURE_Y);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MOVE));
    if (g_Battle.target_selector & 0x40) {
        TASK(Magic109Task)->screen_x.value = g_BMagicSwirlStartPoints[g_Battle.scroll_dir].x;
        TASK(Magic109Task)->screen_y.value = g_BMagicSwirlStartPoints[g_Battle.scroll_dir].y;
    } else {
        TASK(Magic109Task)->screen_x.value = g_BMagicSwirlStartPoints[g_Battle.scroll_dir ^ 2].x;
        TASK(Magic109Task)->screen_y.value = g_BMagicSwirlStartPoints[g_Battle.scroll_dir ^ 2].y;
    }
    TASK(Magic109Task)->twist = 0;
    TASK(Magic109Task)->header.mode += 1;
}

/* func_801EEEAC */
MATCH void BMagic_SwirlGrow(void) {
    u8 radius;

    radius                     = TASK(Magic109Task)->radius + BMAGIC_SWIRL_RADIUS_STEP;
    TASK(Magic109Task)->radius = radius;
    if ((radius & BYTE_MASK) == BMAGIC_SWIRL_RADIUS_MAX) {
        TASK(Magic109Task)->header.mode += 1;
        TASK(Magic109Task)->timer = BMAGIC_SWIRL_HOLD_FRAMES;
    }
    BMagic_SwirlDraw(TASK(Magic109Task)->twist);
}

/* func_801EEF30 */
MATCH void BMagic_SwirlHold(void) {
    s32 twist;
    u8  timer;

    timer                     = TASK(Magic109Task)->timer;
    TASK(Magic109Task)->timer = timer + 0xFF;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        TASK(Magic109Task)->header.mode += 1;
    }
    BMagic_SwirlDraw(TASK(Magic109Task)->twist);
    if (TASK(Magic109Task)->twist_down == 0) {
        twist                     = TASK(Magic109Task)->twist + BMAGIC_SWIRL_TWIST_STEP;
        TASK(Magic109Task)->twist = twist;
        if (twist >= BMAGIC_SWIRL_TWIST_MAX) {
            TASK(Magic109Task)->twist_down = 1;
        }
    } else {
        twist                     = TASK(Magic109Task)->twist - BMAGIC_SWIRL_TWIST_STEP;
        TASK(Magic109Task)->twist = twist;
        if (twist < BMAGIC_SWIRL_TWIST_MIN) {
            TASK(Magic109Task)->twist_down = 0;
        }
    }
}

/* func_801EF008 */
MATCH void BMagic_SwirlShrink(void) {
    u8  radius;
    s32 twist;

    radius                     = TASK(Magic109Task)->radius - BMAGIC_SWIRL_RADIUS_STEP;
    TASK(Magic109Task)->radius = radius;
    if (radius == BMAGIC_SWIRL_RADIUS_START) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
        return;
    }
    BMagic_SwirlDraw(TASK(Magic109Task)->twist);
    if (TASK(Magic109Task)->twist_down == 0) {
        twist                     = TASK(Magic109Task)->twist + BMAGIC_SWIRL_TWIST_STEP;
        TASK(Magic109Task)->twist = twist;
        if (twist >= BMAGIC_SWIRL_TWIST_MAX) {
            TASK(Magic109Task)->twist_down = 1;
        }
    } else {
        twist                     = TASK(Magic109Task)->twist - BMAGIC_SWIRL_TWIST_STEP;
        TASK(Magic109Task)->twist = twist;
        if (twist < BMAGIC_SWIRL_TWIST_MIN) {
            TASK(Magic109Task)->twist_down = 0;
        }
    }
}

/* Draws the swirl: a mesh of texture points, then eight bands of 16 Gouraud quads, each
 * band twisted by the twist times its depth, the quads mirrored when the twist is not positive. */
/* func_801EF0F8 */
MATCH void BMagic_SwirlDraw(s32 twist) {
    RECT      move;
    s32       ring_angle;
    s8        ring;
    s8        segment;
    Offset2*  outer;
    Offset2*  inner;
    POLY_F4*  shadow;
    POLY_GT4* quad;

    ring_angle = 0;
    for (ring = 0; ring < BMAGIC_SWIRL_RINGS + 1; ring++) {
        for (segment = 0; segment < BMAGIC_SWIRL_SEGMENTS; segment++) {
            g_BMagicSwirlTexOffsets[ring][segment].x = (rsin(segment << 8) * ring * (TASK(Magic109Task)->radius >> 3)) >> 12;
            g_BMagicSwirlTexOffsets[ring][segment].y = (rcos(segment << 8) * ring * (TASK(Magic109Task)->radius >> 3)) >> 12;
        }
    }
    move.x = TASK(Magic109Task)->screen_x.value - TASK(Magic109Task)->radius;
    move.y = TASK(Magic109Task)->screen_y.value - TASK(Magic109Task)->radius + g_GfxBufferIndex * SCREEN_HEIGHT;
    move.h = move.w = TASK(Magic109Task)->radius * 2;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &move, BMAGIC_SWIRL_TEXTURE_X, BMAGIC_SWIRL_TEXTURE_Y);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MOVE));
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, BMAGIC_SWIRL_TEXTURE_X, BMAGIC_SWIRL_TEXTURE_Y));
    for (ring = 0; ring < BMAGIC_SWIRL_SEGMENTS; ring++) {
        g_BMagicSwirlOuter[ring].x = FIXED_MUL(rsin(ring << 8), TASK(Magic109Task)->radius);
        g_BMagicSwirlOuter[ring].y = FIXED_MUL(rcos(ring << 8), TASK(Magic109Task)->radius);
    }
    for (ring = BMAGIC_SWIRL_RINGS - 1; ring >= 0; ring--) {
        ring_angle += twist * (BMAGIC_SWIRL_RINGS - ring);
        for (segment = 0; segment < BMAGIC_SWIRL_SEGMENTS; segment++) {
            g_BMagicSwirlInner[segment].x = (rsin(ring_angle + (segment << 8)) * ring * (TASK(Magic109Task)->radius >> 3)) >> 12;
            g_BMagicSwirlInner[segment].y = (rcos(ring_angle + (segment << 8)) * ring * (TASK(Magic109Task)->radius >> 3)) >> 12;
        }
        outer = g_BMagicSwirlOuter;
        inner = g_BMagicSwirlInner;
        for (segment = 0; segment < BMAGIC_SWIRL_SEGMENTS; segment++) {
            shadow = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(shadow);
            setRGB0(shadow, 0, 0, 0);
            quad = (POLY_GT4*)(g_GfxPrimCursor + sizeof(POLY_F4));
            SetPolyGT4(quad);
            quad->tpage = getTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, BMAGIC_SWIRL_TEXTURE_X, BMAGIC_SWIRL_TEXTURE_Y);
            setRGB0(quad, (ring + 1) * 16, (ring + 1) * 16, (ring + 1) * 16);
            setRGB1(quad, (ring + 1) * 16, (ring + 1) * 16, (ring + 1) * 16);
            setRGB2(quad, ring * 16, ring * 16, ring * 16);
            setRGB3(quad, ring * 16, ring * 16, ring * 16);
            if (TASK(Magic109Task)->twist > 0) {
                shadow->x0 = quad->x0 = TASK(Magic109Task)->screen_x.value + outer->x;
                shadow->y0 = quad->y0 = TASK(Magic109Task)->screen_y.value + outer->y;
                outer                 = &g_BMagicSwirlOuter[(segment + 1) & BMAGIC_SWIRL_WRAP];
                shadow->x1 = quad->x1 = TASK(Magic109Task)->screen_x.value + outer->x;
                shadow->y1 = quad->y1 = TASK(Magic109Task)->screen_y.value + outer->y;
                shadow->x2 = quad->x2 = TASK(Magic109Task)->screen_x.value + inner->x;
                shadow->y2 = quad->y2 = TASK(Magic109Task)->screen_y.value + inner->y;
                inner                 = &g_BMagicSwirlInner[(segment + 1) & BMAGIC_SWIRL_WRAP];
                shadow->x3 = quad->x3 = TASK(Magic109Task)->screen_x.value + inner->x;
                shadow->y3 = quad->y3 = TASK(Magic109Task)->screen_y.value + inner->y;
                setUV4(quad, TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring + 1][segment & BMAGIC_SWIRL_WRAP].x,
                       TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring + 1][segment & BMAGIC_SWIRL_WRAP].y,
                       TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring + 1][(segment + 1) & BMAGIC_SWIRL_WRAP].x,
                       TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring + 1][(segment + 1) & BMAGIC_SWIRL_WRAP].y,
                       TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring][segment & BMAGIC_SWIRL_WRAP].x,
                       TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring][segment & BMAGIC_SWIRL_WRAP].y,
                       TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring][(segment + 1) & BMAGIC_SWIRL_WRAP].x,
                       TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring][(segment + 1) & BMAGIC_SWIRL_WRAP].y);
            } else {
                shadow->x1 = quad->x1 = TASK(Magic109Task)->screen_x.value + outer->x;
                shadow->y1 = quad->y1 = TASK(Magic109Task)->screen_y.value + outer->y;
                outer                 = &g_BMagicSwirlOuter[(segment + 1) & BMAGIC_SWIRL_WRAP];
                shadow->x0 = quad->x0 = TASK(Magic109Task)->screen_x.value + outer->x;
                shadow->y0 = quad->y0 = TASK(Magic109Task)->screen_y.value + outer->y;
                shadow->x3 = quad->x3 = TASK(Magic109Task)->screen_x.value + inner->x;
                shadow->y3 = quad->y3 = TASK(Magic109Task)->screen_y.value + inner->y;
                inner                 = &g_BMagicSwirlInner[(segment + 1) & BMAGIC_SWIRL_WRAP];
                shadow->x2 = quad->x2 = TASK(Magic109Task)->screen_x.value + inner->x;
                shadow->y2 = quad->y2 = TASK(Magic109Task)->screen_y.value + inner->y;
                quad->u1              = TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring + 1][segment & BMAGIC_SWIRL_WRAP].x;
                quad->v1              = TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring + 1][segment & BMAGIC_SWIRL_WRAP].y;
                quad->u0              = TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring + 1][(segment + 1) & BMAGIC_SWIRL_WRAP].x;
                quad->v0              = TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring + 1][(segment + 1) & BMAGIC_SWIRL_WRAP].y;
                quad->u3              = TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring][segment & BMAGIC_SWIRL_WRAP].x;
                quad->v3              = TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring][segment & BMAGIC_SWIRL_WRAP].y;
                quad->u2              = TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring][(segment + 1) & BMAGIC_SWIRL_WRAP].x;
                quad->v2              = TASK(Magic109Task)->radius + g_BMagicSwirlTexOffsets[ring][(segment + 1) & BMAGIC_SWIRL_WRAP].y;
            }
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_F4));
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
        }
        for (segment = 0; segment < BMAGIC_SWIRL_SEGMENTS; segment++) {
            g_BMagicSwirlOuter[segment] = g_BMagicSwirlInner[segment];
        }
    }
}
