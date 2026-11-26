#include "magic114_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC44(void) {
    Callback handlers[7];
    s32      tpage;

    __builtin_memcpy(handlers, D_801EEC04, sizeof(handlers));
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.mode != 0) {
        func_801EF128();
    }
    SYS_DISPATCH_BYTE(handlers, TASK(PartyMember)->header.mode);
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

MATCH void func_801EEDA0(void) {
    PartyMember* work;
    PartyMember* battler;
    u16*         dst;
    u16*         src;
    u16*         row_dst;
    u16*         row_src;
    u32          i;

    i       = 0;
    dst     = g_AreaPaletteCopy->rows[26].colors;
    src     = g_AreaPaletteArena->rows[26].colors;
    row_dst = g_AreaPaletteCopy->rows[2].colors;
    row_src = g_AreaPaletteArena->rows[2].colors;
    for (; i < AREA_PALETTE_COLORS; i++) {
        *row_dst = *row_src++ | PSX_COLOR_STP_BIT;
        *dst     = *src++;
        row_dst += 1;
        dst += 1;
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    work                      = TASK(PartyMember);
    battler                   = g_BattleEffectBattler;
    work->pos.x.fixed         = battler->pos.x.fixed;
    work->pos.y.fixed         = battler->pos.y.fixed;
    work->pos.z.fixed         = battler->pos.z.fixed;
    work->timer               = 0;
    TASK(PartyMember)->header.mode += 1;
}

MATCH void func_801EEE84(void) {
    u8 count;

    count                    = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = count;
    if ((count & BYTE_MASK) >= 0x21U) {
        TASK(PartyMember)->header.mode += 1;
        TASK(PartyMember)->unk_09 = 0;
    }
}

MATCH void func_801EEEE4(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) >= 0x21U) {
        TASK(PartyMember)->header.mode += 1;
        TASK(PartyMember)->unk_09 = 0;
    }
}

MATCH void func_801EEF44(void) {
    u8  count;
    u32 slot;

    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) < 0x20U) {
        return;
    }
    TASK(PartyMember)->header.mode += 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x01));
    slot                               = Battle_AllocEffect(1, 7) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].unk_08       = g_BattleEffectBattler->facing;
    g_BattleEffects[slot].target.party = g_BattleEffectBattler;
}

MATCH void func_801EEFFC(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        TASK(PartyMember)->header.mode += 1;
        return;
    }
    func_801F0FBC();
}

MATCH void func_801EF060(void) {
    u8 count;

    count                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = count;
    if (!(count & BYTE_MASK)) {
        TASK(PartyMember)->header.mode += 1;
        TASK(PartyMember)->unk_09 = 0x40;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownAndMarkDamaged.h"

MATCH void func_801EF128(void) {
    s32 values[8];
    s32 pos_x;
    s32 pos_y;
    u8* prim;
    u32 i;
    u32 row;

    func_801EF6A8();
    prim = g_GfxPrimCursor;
    i    = 0;
    do {
        row                       = i & 3;
        TASK(PartyMember)->unk_0C = D_801F11F4[row][0] * TASK(PartyMember)->timer;
        TASK(PartyMember)->unk_10 = D_801F11F4[row][1] * TASK(PartyMember)->timer;
        Effect_RotatePosition(g_Task);
        TASK(PartyMember)->pos.x.fixed = TASK(PartyMember)->unk_0C;
        TASK(PartyMember)->pos.y.fixed = TASK(PartyMember)->unk_10;
        TASK(PartyMember)->unk_0C      = D_801F11F4[row + 1][0] * TASK(PartyMember)->timer;
        TASK(PartyMember)->unk_10      = D_801F11F4[row + 1][1] * TASK(PartyMember)->timer;
        Effect_RotatePosition(g_Task);
        TASK(PartyMember)->param.unk_0B = i;
        func_801EF280(values);
        i++;
    } while (i < 8);
    pos_x = g_BattleEffectBattler->pos.x.fixed;
    pos_y = g_BattleEffectBattler->pos.y.fixed;
    func_800AF0F8(pos_x, pos_y, values, prim, 8, 0x1C, 2);
    PopMatrix();
}

/* One segment of the fan: a three-vertex Gouraud triangle from the task's two points to the
 * apex, shaded by the segment index, flashed in mode 2 and brightened in modes 3 and 4. */
MATCH void func_801EF280(s32* values) {
    POLY_G3* prim;
    long     p;
    long     flag;
    u32      frame;
    u32      phase;

    prim = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(prim);

    setVector(&g_ScratchPadVectors[0], TASK(PartyMember)->pos.x.fixed >> 9, TASK(PartyMember)->pos.y.fixed >> 9, 0);
    setVector(&g_ScratchPadVectors[1], TASK(PartyMember)->unk_0C >> 9, TASK(PartyMember)->unk_10 >> 9, 0);
    g_ScratchPadVectors[2].vx = 0;
    g_ScratchPadVectors[2].vy = 0;
    if (TASK(PartyMember)->param.unk_0B < 4) {
        g_ScratchPadVectors[2].vz = TASK(PartyMember)->timer * 3;
    } else {
        g_ScratchPadVectors[2].vz = -(TASK(PartyMember)->timer * 6) / 2;
    }

    values[TASK(PartyMember)->param.unk_0B] = RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &flag);

    switch (TASK(PartyMember)->param.unk_0B) {
        case 0:
        case 2:
            setRGB0(prim, 0x36, 0x36, 0xB0);
            setRGB1(prim, 0x36, 0x36, 0xB0);
            setRGB2(prim, 0x36, 0x36, 0xC0);
            break;
        case 1:
        case 3:
            setRGB0(prim, 0x40, 0x40, 0xC0);
            setRGB1(prim, 0x40, 0x40, 0xC0);
            setRGB2(prim, 0x40, 0x40, 0xC0);
            break;
        case 4:
        case 6:
            setRGB0(prim, 0x46, 0x46, 0xB0);
            setRGB1(prim, 0x46, 0x46, 0xB0);
            setRGB2(prim, 0x46, 0x46, 0xC0);
            break;
        case 5:
        case 7:
            setRGB0(prim, 0x50, 0x50, 0xC0);
            setRGB1(prim, 0x50, 0x50, 0xC0);
            setRGB2(prim, 0x50, 0x50, 0xC0);
            break;
    }

    if (TASK(PartyMember)->header.mode == 2) {
        frame = g_FrameCount;
        if ((frame & 0x18) == 0 && TASK(PartyMember)->param.unk_0B >= 4) {
            phase = frame & 6;
            if ((TASK(PartyMember)->param.unk_0B & 3) == phase >> 1) {
                setRGB0(prim, 0x80, 0x80, 0xC0);
                setRGB1(prim, 0x80, 0x80, 0xC0);
                setRGB2(prim, 0x80, 0x80, 0xC0);
            }
        }
    }

    if (TASK(PartyMember)->header.mode == 3 || TASK(PartyMember)->header.mode == 4) {
        switch (TASK(PartyMember)->param.unk_0B) {
            case 1:
                prim->r1 = TASK(PartyMember)->unk_09 * 5 + 0x40;
                prim->g1 = TASK(PartyMember)->unk_09 * 4 + 0x40;
                prim->b1 = 0xC0 - TASK(PartyMember)->unk_09 * 2;
                break;
            case 2:
                prim->r0 = TASK(PartyMember)->unk_09 * 5 + 0x36;
                prim->g0 = TASK(PartyMember)->unk_09 * 4 + 0x36;
                prim->b0 = 0xB0 - TASK(PartyMember)->unk_09;
                break;
            case 5:
                prim->r1 = TASK(PartyMember)->unk_09 * 4 + 0x50;
                prim->g1 = TASK(PartyMember)->unk_09 * 3 + 0x50;
                prim->b1 = 0xC0 - TASK(PartyMember)->unk_09 * 2;
                break;
            case 6:
                prim->r0 = TASK(PartyMember)->unk_09 * 4 + 0x46;
                prim->g0 = TASK(PartyMember)->unk_09 * 3 + 0x46;
                prim->b0 = 0xB0 - TASK(PartyMember)->unk_09;
                break;
        }
    }

    g_GfxPrimCursor += sizeof(POLY_G3);
}

MATCH void func_801EF6A8(void) {
    PartyMember* src;
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;

    PushMatrix();
    setVector(&rot, 0, 0, ((TASK(PartyMember)->timer & 0x1F) - 2) << 7);
    src = (PartyMember*)g_BattleEffectBattler;
    setVector(&pos, (src->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (src->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -(COORD_INT(src->pos.z) + 0x200) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

/* func_801EF774 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF7B8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 3), 2, g_Task);
}

MATCH void func_801EF7FC(void) {
    PartyMember* work;

    func_800AFD9C();
    TASK(PartyMember)->unk_14 = TASK(PartyMember)->pos.z.part.integer;
    TASK(PartyMember)->unk_0C = D_801F11F4[2][0] * 32;
    TASK(PartyMember)->unk_10 = D_801F11F4[2][1] * 32;
    Effect_RotatePosition(g_Task);
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + TASK(PartyMember)->unk_10;
    work                           = TASK(PartyMember);
    work->pos.z.part.integer       = g_BattleEffectBattler->pos.z.part.integer + 0x200;
    work->timer                    = 0;
    work->unk_09                   = 0;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF8C0(void) {
    u8 slot;
    u8 count;

    func_801EFA80();
    slot                                   = Battle_AllocEffect(1, 7);
    g_BattleEffects[slot].target.party     = g_BattleEffectBattler;
    g_BattleEffects[slot].header.mode      = 2;
    g_BattleEffects[slot].unk_08           = g_BattleEffectBattler->facing;
    g_BattleEffects[slot].pos.x.fixed      = g_AreaScrollTargetX + TASK(PartyMember)->unk_0C;
    g_BattleEffects[slot].pos.y.fixed      = g_AreaScrollTargetY + TASK(PartyMember)->unk_10;
    COORD_INT(g_BattleEffects[slot].pos.z) = TASK(PartyMember)->unk_14;
    if (TASK(PartyMember)->unk_09 == 0) {
        slot                                   = Battle_AllocEffect(1, 7);
        g_BattleEffects[slot].header.mode      = 1;
        g_BattleEffects[slot].target.party     = g_BattleEffectBattler;
        g_BattleEffects[slot].unk_08           = TASK(PartyMember)->facing;
        g_BattleEffects[slot].unk_0C           = TASK(PartyMember)->unk_0C;
        g_BattleEffects[slot].unk_10           = TASK(PartyMember)->unk_10;
        COORD_INT(g_BattleEffects[slot].pos.z) = TASK(PartyMember)->unk_14;
        g_BattleEffects[slot].arg.unk_09       = 0x10;
        g_BattleEffects[slot].unk_0B           = 0;
    }
    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if (count >= 13) {
        Effect_Reset();
    }
}

MATCH void func_801EFA80(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    u32      frame;
    u32      phase;
    s32      x;
    s32      y;
    s32      tpage;

    TASK(PartyMember)->unk_0C = 0x28000;
    TASK(PartyMember)->unk_10 = 0xA0000 - (TASK(PartyMember)->unk_09 << 17);
    Effect_RotatePosition(g_Task);
    x     = g_AreaScrollTargetX + TASK(PartyMember)->unk_0C;
    y     = g_AreaScrollTargetY + TASK(PartyMember)->unk_10;
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    TASK(PartyMember)->unk_0C = 0;
    TASK(PartyMember)->unk_10 = -0x1000;
    Effect_RotatePosition(g_Task);
    setVector(&g_ScratchPadVectors[0], ((TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C) >> 9) - AREA_CELL_ORIGIN,
              ((TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10) >> 9) - AREA_CELL_ORIGIN, -COORD_INT(TASK(PartyMember)->pos.z) / 2);
    TASK(PartyMember)->unk_0C = 0;
    TASK(PartyMember)->unk_10 = 0x1000;
    Effect_RotatePosition(g_Task);
    setVector(&g_ScratchPadVectors[1], ((TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C) >> 9) - AREA_CELL_ORIGIN,
              ((TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10) >> 9) - AREA_CELL_ORIGIN, -COORD_INT(TASK(PartyMember)->pos.z) / 2);
    TASK(PartyMember)->unk_10 = 0xA8000 - ((TASK(PartyMember)->unk_09 * 3) << 15);
    TASK(PartyMember)->unk_0C = 0x28000;
    Effect_RotatePosition(g_Task);
    setVector(&g_ScratchPadVectors[3], ((g_AreaScrollTargetX + TASK(PartyMember)->unk_0C) >> 9) - AREA_CELL_ORIGIN, ((g_AreaScrollTargetY + TASK(PartyMember)->unk_10) >> 9) - AREA_CELL_ORIGIN,
              -TASK(PartyMember)->unk_14 / 2);
    setVector(&g_ScratchPadVectors[2], (x >> 9) - AREA_CELL_ORIGIN, (y >> 9) - AREA_CELL_ORIGIN, -TASK(PartyMember)->unk_14 / 2);
    RotAverage4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                &flag);
    setRGB0(prim, 16, 1, 1);
    setRGB1(prim, 16, 1, 1);
    setRGB2(prim, 224, 64, 64);
    setRGB3(prim, 1, 1, 1);
    Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
}

MATCH void func_801EFDD8(void) {
    SYS_DISPATCH_BYTE(D_801F1230, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        func_801F093C();
        func_801F04D4(TASK(PartyMember)->param.unk_0B);
        func_801F0004();
    }
}

MATCH void func_801EFE70(void) {
    PartyMember* timer_task;
    PartyMember* position_task;
    PartyMember* clear_task;
    u8           timer;
    s32          x;
    s32          x_offset;
    s32          y;
    s32          y_offset;

    timer_task         = TASK(PartyMember);
    timer              = timer_task->unk_09 - 1;
    timer_task->unk_09 = timer;
    if (timer == 0) {
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 2));
        position_task               = TASK(PartyMember);
        x                           = g_AreaScrollTargetCoordX.fixed;
        x_offset                    = position_task->unk_0C;
        position_task->pos.x.fixed  = x + x_offset;
        y                           = g_AreaScrollTargetCoordY.fixed;
        y_offset                    = position_task->unk_10;
        position_task->param.unk_0B = 0;
        position_task->pos.y.fixed  = y + y_offset;
        TASK(PartyMember)->unk_09   = 16;
        clear_task                  = TASK(PartyMember);
        clear_task->unk_14          = 0;
        clear_task->unk_20          = 0;
        clear_task->header.step     = clear_task->header.step + 1;
    }
}

/* func_801EFF1C */
MATCH void BMagic_ApplyDamageFlags(void) {
    s32 value;

    TASK(PartyMember)->unk_20 -= 5;
    if (TASK(PartyMember)->unk_14 == 0x30) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
    }
    value                     = TASK(PartyMember)->unk_14 + 2;
    TASK(PartyMember)->unk_14 = value;
    if (value == 0xC0) {
        TASK(PartyMember)->param.unk_0B = 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFFB0(void) {
    PartyMember* work  = TASK(PartyMember);
    u8           timer = work->unk_09 - 1;
    work->unk_09       = timer;
    work->unk_20 -= 5;
    work->unk_14 += 2;
    if (timer == 0) {
        Effect_Reset();
    }
}

MATCH void func_801F0004(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;
    s32       left;
    s32       x;
    s32       y;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    TASK(PartyMember)->unk_0C = 0x80000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    x = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
    y = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
    setVector(&g_ScratchPadVectors[2], (x >> 9) - AREA_CELL_ORIGIN, (y >> 9) - AREA_CELL_ORIGIN, -COORD_INT(TASK(PartyMember)->pos.z) / 2);
    TASK(PartyMember)->unk_0C = -0x30000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    x = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
    y = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
    setVector(&g_ScratchPadVectors[3], (x >> 9) - AREA_CELL_ORIGIN, (y >> 9) - AREA_CELL_ORIGIN, -COORD_INT(TASK(PartyMember)->pos.z) / 2);
    for (i = 1; i < TASK(PartyMember)->unk_14 && i < 56; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[2].vz;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vz = g_ScratchPadVectors[3].vz;
        left                      = TASK(PartyMember)->unk_14 - i;
        if (left < 32) {
            TASK(PartyMember)->unk_0C = left << 14;
        } else {
            TASK(PartyMember)->unk_0C = 0x80000;
        }
        TASK(PartyMember)->unk_10 = i * -0x8000;
        Effect_RotatePosition(g_Task);
        x                         = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
        y                         = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
        g_ScratchPadVectors[2].vx = (x >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[2].vy = (y >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[2].vz = -COORD_INT(TASK(PartyMember)->pos.z) / 2;
        left                      = TASK(PartyMember)->unk_14 - i;
        if (left < 8) {
            TASK(PartyMember)->unk_0C = -((left * 3) << 13);
        } else {
            TASK(PartyMember)->unk_0C = -0x30000;
        }
        TASK(PartyMember)->unk_10 = i * -0x8000;
        Effect_RotatePosition(g_Task);
        x                            = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
        y                            = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
        g_ScratchPadVectors[3].vx    = (x >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[3].vy    = (y >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[3].vz    = -COORD_INT(TASK(PartyMember)->pos.z) / 2;
        prim->tpage                  = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 832, 256);
        prim->clut                   = GetClut(0, 482);
        g_ScratchPad.cells.halves[0] = (u32)(TASK(PartyMember)->unk_20 + i * 4) % 188 + 64;
        setUV4(prim, 64, g_ScratchPad.cells.halves[0], 192, g_ScratchPad.cells.halves[0], 64, g_ScratchPad.cells.halves[0] + 3, 192, g_ScratchPad.cells.halves[0] + 3);
        RotAverage4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                    &flag);
        if (TASK(PartyMember)->header.step < 2) {
            g_ScratchPad.cells.halves[1] = (rsin(((g_FrameCount + i) & 0x3F) << 6) * 32 >> 12) + 160;
            setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        } else {
            g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 * 10;
            setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        }
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_FT4));
    }
}

MATCH void func_801F04D4(s32 semi) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;
    s32       left;
    s32       x;
    s32       y;
    u8        trans;

    trans = semi;
    tpage = getTPage(TPAGE_DEPTH_8BIT, semi, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    TASK(PartyMember)->unk_0C = 0x80000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    x = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
    y = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
    setVector(&g_ScratchPadVectors[2], (x >> 9) - AREA_CELL_ORIGIN, (y >> 9) - AREA_CELL_ORIGIN, -COORD_INT(TASK(PartyMember)->pos.z) / 2);
    TASK(PartyMember)->unk_0C = -0x30000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    x = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
    y = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
    setVector(&g_ScratchPadVectors[3], (x >> 9) - AREA_CELL_ORIGIN, (y >> 9) - AREA_CELL_ORIGIN, -COORD_INT(TASK(PartyMember)->pos.z) / 2);
    for (i = 1; i < TASK(PartyMember)->unk_14; i++) {
        if (i >= 56) {
            break;
        }
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetSemiTrans(prim, trans);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[2].vz;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vz = g_ScratchPadVectors[3].vz;
        left                      = TASK(PartyMember)->unk_14 - i;
        if (left < 32) {
            TASK(PartyMember)->unk_0C = left << 14;
        } else {
            TASK(PartyMember)->unk_0C = 0x80000;
        }
        TASK(PartyMember)->unk_10 = i * -0x8000;
        Effect_RotatePosition(g_Task);
        x                         = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
        y                         = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
        g_ScratchPadVectors[2].vx = (x >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[2].vy = (y >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[2].vz = -COORD_INT(TASK(PartyMember)->pos.z) / 2;
        left                      = TASK(PartyMember)->unk_14 - i;
        if (left < 8) {
            TASK(PartyMember)->unk_0C = -((left * 3) << 13);
        } else {
            TASK(PartyMember)->unk_0C = -0x30000;
        }
        TASK(PartyMember)->unk_10 = i * -0x8000;
        Effect_RotatePosition(g_Task);
        x                            = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
        y                            = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
        g_ScratchPadVectors[3].vx    = (x >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[3].vy    = (y >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[3].vz    = -COORD_INT(TASK(PartyMember)->pos.z) / 2;
        prim->tpage                  = GetTPage(TPAGE_DEPTH_8BIT, trans, 832, 256);
        prim->clut                   = GetClut(0, 482);
        g_ScratchPad.cells.halves[0] = (i & 0xF) * 12 + 64;
        setUV4(prim, 0, g_ScratchPad.cells.halves[0], 196, g_ScratchPad.cells.halves[0], 0, g_ScratchPad.cells.halves[0] + 11, 196, g_ScratchPad.cells.halves[0] + 11);
        RotAverage4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                    &flag);
        g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 << 3;
        setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_FT4));
    }
}

MATCH void func_801F093C(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    u32      frame;
    u32      phase;
    s32      i;
    s32      tpage;
    s32      left;
    s32      x;
    s32      y;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    TASK(PartyMember)->unk_0C = -0x30000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    x                         = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
    y                         = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
    g_ScratchPadVectors[1].vx = (x >> 9) - AREA_CELL_ORIGIN;
    g_ScratchPadVectors[1].vy = (y >> 9) - AREA_CELL_ORIGIN;
    TASK(PartyMember)->unk_0C = -0x50000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    x                         = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
    y                         = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
    g_ScratchPadVectors[3].vx = (x >> 9) - AREA_CELL_ORIGIN;
    g_ScratchPadVectors[3].vy = (y >> 9) - AREA_CELL_ORIGIN;
    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = -COORD_INT(TASK(PartyMember)->pos.z) / 2;
    for (i = 1; i < TASK(PartyMember)->unk_14; i++) {
        if (i >= 56) {
            break;
        }
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        left                      = TASK(PartyMember)->unk_14 - i;
        if (left < 8) {
            TASK(PartyMember)->unk_0C = -((left * 3) << 13);
        } else {
            TASK(PartyMember)->unk_0C = -0x30000;
        }
        TASK(PartyMember)->unk_10 = i * -0x8000;
        Effect_RotatePosition(g_Task);
        x                         = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
        y                         = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
        g_ScratchPadVectors[1].vx = (x >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[1].vy = (y >> 9) - AREA_CELL_ORIGIN;
        left                      = TASK(PartyMember)->unk_14 - i;
        if (left < 8) {
            TASK(PartyMember)->unk_0C = -((left * 5) << 13);
        } else {
            TASK(PartyMember)->unk_0C = -0x50000;
        }
        TASK(PartyMember)->unk_10 = i * -0x8000;
        Effect_RotatePosition(g_Task);
        x                         = TASK(PartyMember)->pos.x.fixed + TASK(PartyMember)->unk_0C;
        y                         = TASK(PartyMember)->pos.y.fixed + TASK(PartyMember)->unk_10;
        g_ScratchPadVectors[3].vx = (x >> 9) - AREA_CELL_ORIGIN;
        g_ScratchPadVectors[3].vy = (y >> 9) - AREA_CELL_ORIGIN;
        RotAverage4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                    &flag);
        g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 << 2;
        setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        setRGB1(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
}

MATCH void func_801F0D08(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F1230 + 3, TASK(PartyMember)->header.step);
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801F0D6C(void) {
    PartyMember* work;

    TASK(PartyMember)->unk_25 = 0x1D;
    TASK(PartyMember)->unk_26 = 0;
    TASK(PartyMember)->unk_27 = 0x1A;
    TASK(PartyMember)->unk_28 = 1;
    TASK(PartyMember)->unk_2A = (TASK(PartyMember)->facing - 0x1) & 1;
    TASK(PartyMember)->unk_29 = 4;
    TASK(PartyMember)->unk_24 = 0;
    work                      = TASK(PartyMember);
    work->unk_2B              = 0;
    work->unk_2C.value        = 0;
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->header.step += 1;
    Script_Select(0);
    Area_AddGridActor();
}

MATCH void func_801F0E4C(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Effect_Reset();
        return;
    }
    Area_AddGridActor();
}

MATCH void func_801F0E90(void) {
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;
    PartyMember* battler;
    PartyMember* work;

    PushMatrix();
    if (TASK(PartyMember)->facing & 1) {
        rot.vx = 0x400;
        rot.vy = 0;
    } else {
        rot.vx = 0;
        rot.vy = 0x400;
    }
    rot.vz                    = 0;
    TASK(PartyMember)->unk_0C = 0xC000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    battler                = g_BattleEffectBattler;
    work                   = TASK(PartyMember);
    work->pos.x.fixed      = battler->pos.x.fixed + work->unk_0C;
    work->pos.y.fixed      = battler->pos.y.fixed + work->unk_10;
    COORD_INT(work->pos.z) = COORD_INT(battler->pos.z) + 0x200;
    setVector(&pos, (work->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (work->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -COORD_INT(work->pos.z) / 2);
    RotTrans(&pos, (VECTOR*)matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F0FBC(void) {
    LINE_F2* prim;
    long     depth;
    long     flag;
    long*    rot_flag;
    u32      frame;
    u32      phase;
    u32      i;
    s32      x;
    s32      y;
    s32      z;
    u32      radius;
    u32      shade;
    s32      tpage;

    if (TASK(PartyMember)->unk_09 >= 0x19) {
        func_801F0E90();
        i        = 0;
        x        = TASK(PartyMember)->pos.x.fixed;
        y        = TASK(PartyMember)->pos.y.fixed;
        z        = (TASK(PartyMember)->facing >= 2) ? -2 : 0;
        radius   = ~TASK(PartyMember)->unk_09 & 0x1F;
        shade    = 0x80 - radius * 16;
        rot_flag = &flag;
        do {
            tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5;
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, z, sizeof(DR_MODE));
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            PSX_SET_SEMI_TRANSPARENT(prim);
            g_ScratchPadVectors[0].vx = FIXED_MUL(rcos(i << 6) << 4, radius);
            g_ScratchPadVectors[0].vz = 0;
            g_ScratchPadVectors[0].vy = FIXED_MUL(rsin(i << 6) << 4, radius);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, rot_flag);
            i++;
            g_ScratchPadVectors[0].vx = FIXED_MUL(rcos(i << 6) << 4, radius);
            g_ScratchPadVectors[0].vz = 0;
            g_ScratchPadVectors[0].vy = FIXED_MUL(rsin(i << 6) << 4, radius);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, rot_flag);
            setRGB0(prim, shade, shade, shade);
            Area_CellAddPrim(x, y, z, sizeof(LINE_F2));
        } while (i < 0x40);
        PopMatrix();
    }
}
#else
INCLUDE_ASM(func_801F0FBC);
#endif
