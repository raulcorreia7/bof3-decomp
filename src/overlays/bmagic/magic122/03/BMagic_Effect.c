#include "magic122_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDFC};
    SYS_DISPATCH_TASK(handlers, 1, g_Self);
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

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    battler                   = g_BattleEffectBattler;
    task                      = SELF(PartyMember);
    WorldPos_Copy(&task->pos, &battler->pos);
    slot                               = Battle_AllocEffect(1, 56) & BYTE_MASK;
    owner                              = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 4;
    g_BattleEffects[slot].target.party = owner;
    i                                  = 1;
    dst                                = &g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[1];
    src                                = &g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[1];
    for (; i < 16; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    i    = 1;
    src2 = &g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[1];
    dst2 = &g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[1];
    for (; i < 16; i++) {
        dst2[16] = src2[16];
        dst2++;
        src2++;
    }
    i    = 1;
    src3 = &g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[1];
    dst3 = &g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[1];
    for (; i < 16; i++) {
        dst3[32] = src3[32] | PSX_COLOR_STP_BIT;
        dst3++;
        src3++;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0]  = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[16] = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[32] = 0;
    g_GfxPalettePending                                           = 1;
    SELF(PartyMember)->param.unk_0B                               = 0;
    SELF(PartyMember)->unk_09                                     = 0;
    SELF(PartyMember)->header.mode++;
}

#include "overlays/bmagic/shared/Effect_PlayOnIdleTick.h"

/* func_801EEE5C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEA0(void) {
    SYS_DISPATCH_BYTE(D_801F02D0, SELF(PartyMember)->header.step);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        if (SELF(PartyMember)->header.step != 0) {
            func_801EFBA8();
            func_801EF324();
        }
    }
}

MATCH void func_801EEF2C(void) {
    PartyMember* battler;
    PartyMember* work;

    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
        Battle_CenterCamera();
        Battle_ProjectRange();
        work                         = SELF(PartyMember);
        battler                      = g_BattleEffectBattler;
        g_ScratchPad.cells.halves[6] = work->screen_x.value;
        g_ScratchPad.cells.halves[7] = work->screen_y.value;
        WorldPos_Copy(&work->pos, &battler->pos);
        Battle_ProjectRange();
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            func_800B0118();
        } else {
            switch (SELF(PartyMember)->facing) {
                case 0:
                    SELF(PartyMember)->unk_0C = 41;
                    SELF(PartyMember)->unk_10 = -13;
                    break;
                case 1:
                    SELF(PartyMember)->unk_0C = -41;
                    SELF(PartyMember)->unk_10 = -13;
                    break;
                case 2:
                    SELF(PartyMember)->unk_0C = -38;
                    SELF(PartyMember)->unk_10 = -38;
                    break;
                default:
                    SELF(PartyMember)->unk_0C = 38;
                    SELF(PartyMember)->unk_10 = -38;
                    break;
            }
        }
        SELF(PartyMember)->screen_x.value += SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->screen_y.value += SELF(PartyMember)->unk_10;
        g_ScratchPad.cells.halves[4]    = SELF(PartyMember)->screen_x.value;
        g_ScratchPad.cells.halves[5]    = SELF(PartyMember)->screen_y.value;
        SELF(PartyMember)->unk_14       = ratan2(g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[7] - g_ScratchPad.cells.halves[5]);
        SELF(PartyMember)->unk_04       = 16;
        SELF(PartyMember)->param.unk_0B = 17;
        SELF(PartyMember)->unk_09       = 0;
        SELF(PartyMember)->timer        = 1;
        SELF(PartyMember)->header.step++;
        SND_SEQueueSelection(0x100);
    }
}

MATCH void func_801EF158(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->timer += 3;
    work = SELF(PartyMember);
    work->unk_09++;
    if (work->unk_09 == 8) {
        work = SELF(PartyMember);
        work->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpTimerCallSelector.h"

#include "overlays/bmagic/shared/Effect_CountUpAndStepAt120.h"

#include "overlays/bmagic/shared/Effect_CountUpAndFinishAt136.h"

MATCH void func_801EF324(void) {
    POLY_GT4* prim;
    s32       tpage;
    s32       i;
    s32       inner;
    s32       outer;
    s32       swing;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_14;
    for (i = 1; i < SELF(PartyMember)->timer + 1; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + FIXED_MUL(rsin(((i + SELF(PartyMember)->unk_09) & 0x3F) << 6), 0x100)) & ANGLE_MASK;
        g_ScratchPad.cells.halves[4] += FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 16);
        g_ScratchPad.cells.halves[5] += FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), 16);
        prim  = (POLY_GT4*)g_GfxPrimCursor;
        inner = ((i - 1 - SELF(PartyMember)->unk_09) & 0x3F) << 6;
        outer = ((i - SELF(PartyMember)->unk_09) & 0x3F) << 6;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + 0x400) & ANGLE_MASK;
        swing                        = FIXED_MUL(rsin(inner), 2) + 4;
        g_ScratchPad.cells.halves[0] = (i - 1) * 9 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
        prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        swing                        = FIXED_MUL(rsin(outer), 2) + 4;
        g_ScratchPad.cells.halves[0] = i * 9 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
        prim->x3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y3                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setXY0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        prim->x2    = g_ScratchPad.cells.halves[4];
        prim->y2    = g_ScratchPad.cells.halves[5];
        prim->clut  = GetClut(0, 0x1FA);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100);
        setUV4(prim, 0x40, i * 8 - SELF(PartyMember)->unk_09 * 16, 0x80, i * 8 - SELF(PartyMember)->unk_09 * 16, 0x40, i * 8 - SELF(PartyMember)->unk_09 * 16 + 8, 0x80,
               i * 8 - SELF(PartyMember)->unk_09 * 16 + 8);
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04 * 8;
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04;
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] - 0x400) & ANGLE_MASK;
        swing                        = FIXED_MUL(rsin(inner), 2) + 4;
        g_ScratchPad.cells.halves[0] = (i - 1) * 9 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
        setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        swing                        = FIXED_MUL(rsin(outer), 2) + 4;
        g_ScratchPad.cells.halves[0] = i * 9 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
        prim->x2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x1                     = g_ScratchPad.cells.halves[6];
        prim->y1                     = g_ScratchPad.cells.halves[7];
        prim->x3                     = g_ScratchPad.cells.halves[4];
        prim->y3                     = g_ScratchPad.cells.halves[5];
        prim->clut                   = GetClut(0, 0x1FA);
        prim->tpage                  = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100);
        setUV4(prim, 0, i * 8 - SELF(PartyMember)->unk_09 * 16, 0x40, i * 8 - SELF(PartyMember)->unk_09 * 16, 0, i * 8 - SELF(PartyMember)->unk_09 * 16 + 8, 0x40,
               i * 8 - SELF(PartyMember)->unk_09 * 16 + 8);
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04 * 8;
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04;
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

/* Draws the trail: for each step, two Gouraud quads either side of a path that swings on a sine, widening with the step. */
MATCH void func_801EFBA8(void) {
    POLY_G4* prim;
    s32      iteration;
    s32      inner_angle;
    s32      outer_angle;
    s32      radius;
    s32      previous_iteration;

    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_14;
    iteration                    = 1;
    if (iteration < SELF(PartyMember)->timer + 1) {
        do {
            g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
            g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
            g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + FIXED_MUL(rsin(((iteration + SELF(PartyMember)->unk_09) & 0x3F) << 6), 0x100)) & ANGLE_MASK;
            g_ScratchPad.cells.halves[4] += FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 16);
            g_ScratchPad.cells.halves[5] += FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), 16);
            prim        = (POLY_G4*)g_GfxPrimCursor;
            inner_angle = ((iteration - 1 - SELF(PartyMember)->unk_09) & 0xF) << 8;
            outer_angle = ((iteration - SELF(PartyMember)->unk_09) & 0xF) << 8;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + ANGLE_90) & ANGLE_MASK;
            radius                       = rsin(inner_angle);
            previous_iteration           = iteration - 1;
            radius                       = FIXED_MUL((radius * 3) << 1, previous_iteration) + 4;
            g_ScratchPad.cells.halves[0] = previous_iteration * 18 + radius;
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
            prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
            prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
            radius                       = rsin(outer_angle);
            radius                       = FIXED_MUL((radius * 3) << 1, iteration) + 4;
            g_ScratchPad.cells.halves[0] = iteration * 18 + radius;
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
            prim->x3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
            prim->y3                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
            setXY0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
            prim->x2                     = g_ScratchPad.cells.halves[4];
            prim->y2                     = g_ScratchPad.cells.halves[5];
            g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04 * 4;
            setRGB0(prim, SELF(PartyMember)->unk_04 * 8, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, SELF(PartyMember)->unk_04 * 8, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
            setRGB3(prim, 1, 1, 1);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] - ANGLE_90) & ANGLE_MASK;
            radius                       = rsin(inner_angle);
            radius                       = FIXED_MUL((radius * 3) << 1, previous_iteration) + 4;
            g_ScratchPad.cells.halves[0] = previous_iteration * 18 + radius;
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
            setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
                   g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
            radius                       = rsin(outer_angle);
            radius                       = FIXED_MUL((radius * 3) << 1, iteration) + 4;
            g_ScratchPad.cells.halves[0] = iteration * 18 + radius;
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
            prim->x2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
            prim->y2                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
            iteration++;
            prim->x1                     = g_ScratchPad.cells.halves[6];
            prim->y1                     = g_ScratchPad.cells.halves[7];
            prim->x3                     = g_ScratchPad.cells.halves[4];
            prim->y3                     = g_ScratchPad.cells.halves[5];
            g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04 * 4;
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, SELF(PartyMember)->unk_04 * 8, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, SELF(PartyMember)->unk_04 * 8, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
        } while (iteration < SELF(PartyMember)->timer + 1);
    }
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}
