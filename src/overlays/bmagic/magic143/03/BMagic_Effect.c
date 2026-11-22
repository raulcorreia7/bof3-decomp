#include "magic143_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED24};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* src;
    u32          slot;
    PartyMember* task;

    src                                = g_Battle.selected_actor;
    slot                               = Battle_AllocEffect(1, 53) & BYTE_MASK;
    task                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    g_BattleEffects[slot].pos.x.fixed  = src->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = src->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = src->pos.z.fixed;
    g_Task->param.unk_0B               = 1;
    SND_SEQueueSelection(0x100);
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EED70 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEDB4(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 1), g_Task->header.step);
    func_800AF764();
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF23C(48, 16, 0x3);
        g_Task->param.unk_0B += 4;
        func_801EF23C(32, 80, 0xF);
        g_Task->param.unk_0B += 2;
        Effect_DrawBolt();
        g_Task->param.unk_0B += 4;
        func_801EF23C(24, BOLT_RADIUS, BOLT_FLICKER_MASK);
        g_Task->param.unk_0B -= 10;
        g_Task->screen_x.value += 16;
        func_801EFC74();
        g_Task->screen_x.value -= 32;
        func_801EFC74();
        PopMatrix();
    }
}

MATCH void func_801EEF10(void) {
    g_Task->param.unk_0B = RANDOM_MASK(15);
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.step++;
}

MATCH void func_801EEF78(void) {
    u8 timer;

    g_Task->timer += 4;
    g_Task->param.unk_0B += 1;
    timer = g_Task->timer;
    if (timer == 16) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        GFX_PaletteAllocFade(g_Battle.selected_actor, -8, -8, -8, 1);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 16);
        g_Task->unk_09 = 32;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF054(void) {
    u8  timer;
    u8* selector;

    g_Task->param.unk_0B++;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        selector = &g_BattleTargetSelector;
        Battle_MarkDamaged(*selector);
        func_80196718(g_BattleSelectedActor);
        Battle_FadePoisonedBattler(*selector);
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrixRolled.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EF23C(s32 band_height, u16 radius, u16 jitter_mask) {
    POLY_G4*    prim;
    long        p;
    long        flag;
    s32         depth;
    s32         draw_mode;
    s32         i;
    ScratchPad* scratch;
    SVECTOR*    vectors;
    s32*        cells;

    scratch = SPAD(0u);
    cells   = scratch->cells.words;
    vectors = scratch->vectors;

    cells[0] = (s16)radius / 2;
    cells[1] = (g_Task->param.unk_0B & 0xF) << 8;
    cells[2] = g_Task->timer * 8;
    cells[3] = g_Task->timer * 13;

    vectors[0].vy = FIXED_MUL(rsin(cells[1]), scratch->cells.halves[0]);
    vectors[0].vz = 0;
    depth         = -0x30;
    draw_mode     = 0xA5;
    if (GetGraphType() != 1) {
        if (GetGraphType() != 2) {
            draw_mode = 0x35;
        }
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, draw_mode, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    for (i = 1; i < 24; i++) {
        cells[1] = ((g_Task->param.unk_0B + i) & 0xF) << 8;
        if RANDOM_MASK (1) {
            scratch->cells.halves[0] = (s16)radius + (jitter_mask & rand());
        } else {
            scratch->cells.halves[0] = (s16)radius - (jitter_mask & rand());
        }

        setVector(&vectors[2], 0, vectors[0].vy, vectors[0].vz);
        setVector(&vectors[3], 0, vectors[0].vy - band_height, vectors[0].vz);
        setVector(&vectors[0], 0, FIXED_MUL(rsin(cells[1]), scratch->cells.halves[0]), depth);
        setVector(&vectors[1], 0, vectors[0].vy - band_height, depth);
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, cells[2], cells[2], cells[2]);
        setRGB1(prim, cells[3], cells[3], cells[2]);
        setRGB2(prim, cells[2], cells[2], cells[2]);
        setRGB3(prim, cells[3], cells[3], cells[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&vectors[0], &vectors[1], &vectors[2], &vectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        vectors[0].vy -= band_height;
        vectors[1].vy -= band_height;
        vectors[2].vy -= band_height;
        vectors[3].vy -= band_height;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, cells[3], cells[3], cells[2]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, cells[3], cells[3], cells[2]);
        setRGB3(prim, 1, 1, 1);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&vectors[0], &vectors[1], &vectors[2], &vectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        vectors[0].vy += band_height;
        vectors[1].vy += band_height;
        vectors[2].vy += band_height;
        vectors[3].vy += band_height;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, cells[3], cells[3], cells[2]);
        setRGB1(prim, cells[2], cells[2], cells[2]);
        setRGB2(prim, cells[3], cells[3], cells[2]);
        setRGB3(prim, cells[2], cells[2], cells[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&vectors[0], &vectors[1], &vectors[2], &vectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        vectors[0].vy += band_height;
        vectors[1].vy += band_height;
        vectors[2].vy += band_height;
        vectors[3].vy += band_height;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, cells[3], cells[3], cells[2]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, cells[3], cells[3], cells[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&vectors[0], &vectors[1], &vectors[2], &vectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        depth -= 0x30;
        vectors[0].vy -= band_height * 2;
    }
}

#else
INCLUDE_ASM(func_801EF23C);
#endif

#include "overlays/bmagic/shared/Effect_DrawBolt.h"

MATCH void func_801EFC74(void) {
    POLY_G3* prim;
    s32*     radius;
    s32      i;

    g_ScratchPad.cells.words[0] = (rand() & 7) + g_Task->timer * 4;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    i      = 0;
    radius = &g_ScratchPad.cells.words[0];
    for (; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->screen_x.value, g_Task->screen_y.value, g_Task->screen_x.value + FIXED_MUL(rsin(i << 9), *radius), g_Task->screen_y.value + FIXED_MUL(rcos(i << 9), *radius),
               g_Task->screen_x.value + FIXED_MUL(rsin((i + 1) << 9), *radius), g_Task->screen_y.value + FIXED_MUL(rcos((i + 1) << 9), *radius));
        setRGB0(prim, g_Task->timer * 8, g_Task->timer * 8, g_Task->timer * 6);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
