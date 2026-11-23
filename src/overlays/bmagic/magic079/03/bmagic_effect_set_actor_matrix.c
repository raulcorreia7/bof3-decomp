#include "magic079_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEE64(void) {
    TASK(PartyMember)->pos.x.fixed  = g_BattleSelectedActor->pos.x.fixed - 0x4000;
    TASK(PartyMember)->pos.y.fixed  = g_BattleSelectedActor->pos.y.fixed - 0x4000;
    TASK(PartyMember)->pos.z.fixed  = g_BattleSelectedActor->pos.z.fixed + 0x04000000;
    TASK(PartyMember)->param.unk_0B = 0x10;
    TASK(PartyMember)->unk_09       = 0x10;
    TASK(PartyMember)->timer        = 176;
    TASK(PartyMember)->header.step++;
}

MATCH void func_801EEEE4(void) {
    PartyMember* work = TASK(PartyMember);
    u8           timer;

    work->pos.z.part.integer -= 0x40;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EEF34(void) {
    u8 count;
    u8 value;

    count = TASK(PartyMember)->unk_09;
    if ((count & BYTE_MASK) != 0x20) {
        TASK(PartyMember)->unk_09 = count + 1;
    }
    value                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = value;
    if ((value & BYTE_MASK) == 0x30) {
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EEFB8(void) {
    u8 count;
    u8 timer_next;

    count = TASK(PartyMember)->unk_09;
    if ((count & BYTE_MASK) != 0x20) {
        TASK(PartyMember)->unk_09 = count + 1;
    }
    timer_next               = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 16) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF048(void) {
    PartyMember* work;

    work               = TASK(PartyMember);
    work->timer        = work->timer - 1;
    work               = TASK(PartyMember);
    work->param.unk_0B = work->param.unk_0B - 1;
    if (work->param.unk_0B == 0) {
        Effect_Reset();
    }
}

MATCH void func_801EF0A8(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F02C8, func_801EF458);
}

MATCH void func_801EF130(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->pos.x.fixed  = D_8014637C->pos.x.fixed - 0x4000;
        TASK(PartyMember)->pos.y.fixed  = D_8014637C->pos.y.fixed - 0x4000;
        TASK(PartyMember)->pos.z.fixed  = D_8014637C->pos.z.fixed + 0x04000000;
        TASK(PartyMember)->param.unk_0B = 0x10;
        TASK(PartyMember)->unk_09       = 0x10;
        TASK(PartyMember)->timer        = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF1DC(void) {
    PartyMember* work;
    u8           timer;

    work  = TASK(PartyMember);
    timer = work->unk_09 - 1;
    COORD_INT(work->pos.z) -= 64;
    work->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->unk_09      = 0x20;
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF23C(void) {
    u8 count;
    u8 value;

    count = TASK(PartyMember)->unk_09;
    if (count != 0) {
        TASK(PartyMember)->unk_09 = count - 1;
    }
    value                    = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = value;
    if ((value & BYTE_MASK) == 0x80) {
        TASK(PartyMember)->unk_09 = 0x20;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF2BC(void) {
    u8 count;
    u8 timer_next;

    count = TASK(PartyMember)->unk_09;
    if (count != 0) {
        TASK(PartyMember)->unk_09 = count - 1;
    }
    timer_next               = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 160) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF348(void) {
    PartyMember* work;

    work               = TASK(PartyMember);
    work->timer        = work->timer + 1;
    work               = TASK(PartyMember);
    work->param.unk_0B = work->param.unk_0B - 1;
    if (work->param.unk_0B == 0) {
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

#ifdef NON_MATCHING
/* Draws the effect's spiral: twenty-four rings of eight quads sweep from the effect's start angle,
 * each ring one shade darker and 0x28 deeper; the step 2 and 3 branches flicker the first ring
 * against the radius tables. */
NON_MATCHING void func_801EF458(void) {
    POLY_G4* prim;
    long     p;
    long     flag;
    s16      shade;
    s16      shade2;
    s32      radius;
    s32      ring;
    s32      step;
    s16*     cells;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256), 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[2] = 0;
    g_ScratchPad.cells.halves[7] = TASK(PartyMember)->param.unk_0B << 1;
    shade                        = (3 * rsin((g_FrameCount & 0x3F) << 6)) >> 12;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->timer & 0xF;
    if (TASK(PartyMember)->header.step >= 2) {
        g_ScratchPad.cells.halves[4] = D_801F02DC[g_ScratchPad.cells.halves[6]];
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[7] + ((rsin(g_ScratchPad.cells.halves[6] << 8) << 2) >> 12);
        if (TASK(PartyMember)->header.mode != 0 && TASK(PartyMember)->unk_09 != 0) {
            g_ScratchPad.cells.halves[4] = D_801F031C[g_ScratchPad.cells.halves[6]];
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[7] + ((rsin(g_ScratchPad.cells.halves[6] << 8) << 2) >> 12);
        }
    } else {
        g_ScratchPad.cells.halves[4] = D_801F031C[g_ScratchPad.cells.halves[6]];
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[7] + ((rsin(g_ScratchPad.cells.halves[6] << 8) << 2) >> 12);
    }
    cells  = g_ScratchPad.cells.halves;
    radius = 7;
    for (ring = 1; ring < 25; ring++) {
        cells[3] = cells[2];
        cells[2] = -(ring * 40);
        shade2                       = shade;
        shade                        = (3 * rsin(((g_FrameCount + ring) & 0x3F) << 6) * ring) >> 12;
        cells[5] = cells[4];
        cells[1] = cells[0];
        cells[6] = (TASK(PartyMember)->timer + ring) & 0xF;
        if (TASK(PartyMember)->header.step == 2) {
            cells[4] = D_801F02DC[cells[6]];
            if (cells[6] < 8) {
                cells[0] = cells[7] + FIXED_MUL(rsin(cells[6] << 8), radius);
            } else {
                cells[0] = cells[7] + ((rsin(cells[6] << 8) << 2) >> 12);
            }
            if (TASK(PartyMember)->header.mode != 0 ? (ring < TASK(PartyMember)->unk_09) : (TASK(PartyMember)->unk_09 < ring)) {
                cells[0] = cells[7];
                cells[4] = D_801F031C[cells[6]];
            }
        } else if (TASK(PartyMember)->header.step == 3) {
            cells[4] = D_801F02DC[cells[6]];
            if (cells[6] < 8) {
                cells[0] = cells[7] + FIXED_MUL(rsin(cells[6] << 8), radius);
            } else {
                cells[0] = cells[7] + ((rsin(cells[6] << 8) << 2) >> 12);
            }
            if (TASK(PartyMember)->header.mode != 0 ? (TASK(PartyMember)->unk_09 < ring) : (ring < TASK(PartyMember)->unk_09)) {
                cells[0] = cells[7];
                cells[4] = D_801F031C[cells[6]];
            }
        } else {
            cells[4] = D_801F031C[cells[6]];
            cells[0] = cells[7] + ((rsin(cells[6] << 8) << 2) >> 12);
        }
        g_ScratchPadVectors[1].vx = shade + FIXED_MUL(rcos(0), cells[0]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rsin(0), cells[0]);
        g_ScratchPadVectors[1].vz = cells[2];
        g_ScratchPadVectors[3].vx = shade2 + FIXED_MUL(rcos(0), cells[1]);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rsin(0), cells[1]);
        g_ScratchPadVectors[3].vz = cells[3];
        for (step = 1; step < 9; step++) {
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz;
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz;
            g_ScratchPadVectors[1].vx = shade + FIXED_MUL(rcos(step << 9), cells[0]);
            g_ScratchPadVectors[1].vy = FIXED_MUL(rsin(step << 9), cells[0]);
            g_ScratchPadVectors[1].vz = cells[2];
            g_ScratchPadVectors[3].vx = shade2 + FIXED_MUL(rcos(step << 9), cells[1]);
            g_ScratchPadVectors[3].vy = FIXED_MUL(rsin(step << 9), cells[1]);
            g_ScratchPadVectors[3].vz = cells[3];
            prim                      = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            setRGB0(prim, cells[4], cells[4] / 3, cells[4] / 2);
            setRGB1(prim, cells[4], cells[4] / 3, cells[4] / 2);
            setRGB2(prim, cells[5], cells[5] / 3, cells[5] / 2);
            setRGB3(prim, cells[5], cells[5] / 3, cells[5] / 2);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &p, &flag);
            Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(POLY_G4));
        }
        radius += 3;
    }
}
#else
INCLUDE_ASM(func_801EF458);
#endif

MATCH void func_801EFBEC(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F035C, func_801F002C);
}

MATCH void func_801EFC74(void) {
    PartyMember* src;

    src                            = g_Battle.selected_actor;
    TASK(PartyMember)->pos.x.fixed = src->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed = src->pos.y.fixed;
    TASK(PartyMember)->pos.z       = src->pos.z;
    TASK(PartyMember)->unk_09      = 4;
    TASK(PartyMember)->timer       = 176;
    TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

MATCH void func_801EFD2C(void) {
    TASK(PartyMember)->timer -= 1;
    if (g_BattleEffectBattler->param.unk_0B == TASK(PartyMember)->header.mode) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFD84(void) {
    PartyMember* work;
    PartyMember* active;

    work         = TASK(PartyMember);
    work->timer  = work->timer - 1;
    work         = TASK(PartyMember);
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 4) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = active->param.unk_0B - 1;
        Effect_Reset();
    }
}

MATCH void func_801EFE00(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F036C, func_801F002C);
}

MATCH void func_801EFE88(void) {
    PartyMember* src;
    u8           timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        src                            = D_8014637C;
        TASK(PartyMember)->pos.x.fixed = src->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = src->pos.y.fixed;
        TASK(PartyMember)->pos.z       = src->pos.z;
        TASK(PartyMember)->unk_09      = 4;
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void Effect_CountUpAndStep2(void) {
    BMAGIC_COUNT_UP_AND_STEP();
}

MATCH void func_801EFF58(void) {
    TASK(PartyMember)->timer += 1;
    if (g_BattleEffectBattler->param.unk_0B == TASK(PartyMember)->header.mode) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFFB0(void) {
    PartyMember* work;
    PartyMember* active;

    work         = TASK(PartyMember);
    work->timer  = work->timer + 1;
    work         = TASK(PartyMember);
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 4) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = active->param.unk_0B - 1;
        Effect_Reset();
    }
}

MATCH void func_801F002C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      shade;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 << 4;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);

    for (i = 1; i <= 8; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        shade                        = D_801F037C[TASK(PartyMember)->timer & 0xF];
        g_ScratchPad.cells.halves[4] = shade;
        setRGB0(prim, shade, 240, 240);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
