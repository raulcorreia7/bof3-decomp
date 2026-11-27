#include "magic059_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED0C, func_801EF118);
    Battle_ProjectRange();

    BMAGIC_RUN_EFFECT_SLOTS(D_801F0694, func_801EFE48);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EED0C(void) {
    u16* palette_src;
    u16* palette_dst;
    u32  i;
    u8   slot;
    u8   phase;
    s32  speed;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    SELF(PartyMember)->param.unk_0B    = 0;
    slot                               = Battle_AllocEffect(1, 0x40);
    g_BattleEffects[slot].target.party = g_Self;
    g_BattleEffects[slot].header.mode  = 0;
    SELF(PartyMember)->param.unk_0B++;

    i     = 0;
    speed = 0x80;
    for (; i < 8; i++) {
        slot                                    = BMagic_AllocEffect();
        BMAGIC_EFFECT_SLOTS[slot].target.party  = g_Self;
        BMAGIC_EFFECT_SLOTS[slot].header.mode   = 0;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09    = i << 3;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B        = 3;
        BMAGIC_EFFECT_SLOTS[slot].unk_0C        = speed;
        *(s32*)BMAGIC_EFFECT_SLOTS[slot].pad_14 = 0x800000;
        SELF(PartyMember)->param.unk_0B++;
    }
    speed = 0xC0;
    for (i = 0, phase = 2; i < 8; i++, phase += 8) {
        slot                                    = BMagic_AllocEffect();
        BMAGIC_EFFECT_SLOTS[slot].target.party  = g_Self;
        BMAGIC_EFFECT_SLOTS[slot].header.mode   = 0;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09    = phase;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B        = 2;
        BMAGIC_EFFECT_SLOTS[slot].unk_0C        = speed;
        *(s32*)BMAGIC_EFFECT_SLOTS[slot].pad_14 = 0x400000;
        SELF(PartyMember)->param.unk_0B++;
    }
    speed = 0x100;
    for (i = 0, phase = 4; i < 8; i++, phase += 8) {
        slot                                    = BMagic_AllocEffect();
        BMAGIC_EFFECT_SLOTS[slot].target.party  = g_Self;
        BMAGIC_EFFECT_SLOTS[slot].header.mode   = 0;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09    = phase;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B        = 1;
        BMAGIC_EFFECT_SLOTS[slot].unk_0C        = speed;
        *(s32*)BMAGIC_EFFECT_SLOTS[slot].pad_14 = 0;
        SELF(PartyMember)->param.unk_0B++;
    }

    i           = 0;
    palette_dst = GAME_PALETTE_MIRROR_U16 + 0xB00;
    palette_src = (u16*)GAME_PALETTE_STAGE + 0xB00;
    for (; i < 16; i++) {
        *palette_dst++ = *palette_src++ | 0x8000;
    }
    g_BattleEffectPalette[0] = D_80036C00[0];
    g_Battle.flags |= 0x200;
    g_GfxPalettePending = 1;

    SELF(PartyMember)->facing = g_Battle.active_actor->facing;
    SELF(PartyMember)->unk_0C = 0x40000;
    SELF(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Self);
    /* The Coord reads keep the y load behind the x store. */
    SELF(PartyMember)->unk_18      = g_AreaScrollTargetCoordX.fixed + SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->unk_1C      = g_AreaScrollTargetCoordY.fixed + SELF(PartyMember)->unk_10;
    SELF(PartyMember)->pos.x.fixed = SELF(PartyMember)->unk_18 + (rsin(0) << 6);
    SELF(PartyMember)->pos.y.fixed = SELF(PartyMember)->unk_1C + (rcos(0) << 6);
    func_801F0544();
    SND_SEQueueSelection(0x100);
    SELF(PartyMember)->unk_09 = D_801F065C[SELF(PartyMember)->facing];
    SELF(PartyMember)->header.mode++;
}
#else
INCLUDE_ASM(func_801EED0C);
#endif

/* Moves the effect one step around a circle. */
MATCH void func_801EF118(void) {
    u8           angle;
    s16*         cell;
    PartyMember* work;

    work                           = SELF(PartyMember);
    cell                           = (s16*)&D_1F80000E;
    angle                          = work->unk_09 + 1;
    work->unk_09                   = angle;
    *cell                          = angle << 4;
    SELF(PartyMember)->pos.x.fixed = SELF(PartyMember)->unk_18 + (rsin((s16)(angle << 4)) << 6);
    SELF(PartyMember)->pos.y.fixed = SELF(PartyMember)->unk_1C + (rcos(*cell) << 6);
    if (SELF(PartyMember)->param.unk_0B == 0) {
        func_800A9820(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EF1E0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF224(void) {
    SYS_DISPATCH_BYTE(D_801F0670, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        func_801EF638();
        func_801EF70C(-SELF(PartyMember)->unk_09 & 0x3F, 0x20);
        func_801EF70C((8 - SELF(PartyMember)->unk_09) & 0x3F, 0x20);
        func_801EF70C((16 - SELF(PartyMember)->unk_09) & 0x3F, 0x20);
        func_801EF70C((24 - SELF(PartyMember)->unk_09) & 0x3F, 0x20);
        func_801EF70C((32 - SELF(PartyMember)->unk_09) & 0x3F, 0x20);
        func_801EF70C((40 - SELF(PartyMember)->unk_09) & 0x3F, 0x20);
        func_801EF70C((48 - SELF(PartyMember)->unk_09) & 0x3F, 0x20);
        func_801EF70C((56 - SELF(PartyMember)->unk_09) & 0x3F, 0x20);
        func_801EF70C((4 - SELF(PartyMember)->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((12 - SELF(PartyMember)->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((20 - SELF(PartyMember)->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((28 - SELF(PartyMember)->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((36 - SELF(PartyMember)->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((44 - SELF(PartyMember)->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((52 - SELF(PartyMember)->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((60 - SELF(PartyMember)->unk_09 * 2) & 0x3E, 0x50);
        PopMatrix();
    }
}

MATCH void func_801EF4C4(void) {
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->timer  = 0;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF504(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->unk_09++;
    work = SELF(PartyMember);
    work->timer += 2;
    if (work->timer == 32) {
        work = SELF(PartyMember);
        work->header.step++;
    }
}

MATCH void func_801EF570(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(unk_09, 1, 160);
}

/* func_801EF5C0 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

MATCH void func_801EF638(void) {
    PartyMember* src;
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;

    PushMatrix();
    src = (PartyMember*)g_BattleEffectBattler;
    setVector(&rot, 0, 0, 0);
    SELF(PartyMember)->pos.x.fixed      = src->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed      = src->pos.y.fixed;
    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(src->pos.z);
    setVector(&pos, (SELF(PartyMember)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (SELF(PartyMember)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -COORD_INT(SELF(PartyMember)->pos.z) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

#ifdef NON_MATCHING
/* Draws eleven steps of two quads each: an inner, an outer and a trailing far point sweep a ring whose
 * radii grow by thirteen and whose depth falls by 0x40 a step, the far point one step behind; the
 * shades alternate between the effect ticker and the flat white. */
NON_MATCHING void func_801EF70C(s32 phase, s32 radius) {
    POLY_G4* prim;
    SVECTOR  inner;
    SVECTOR  outer;
    SVECTOR  far;
    long     p;
    long     flag;
    s32      tpage;
    s32      wave;
    s32      i;
    s16*     shade;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));

    shade                        = &g_ScratchPad.cells.halves[6];
    g_ScratchPad.cells.halves[7] = (phase & 0x3F) << 6;
    g_ScratchPad.cells.halves[0] = radius + 0x32;
    g_ScratchPad.cells.halves[1] = radius + 0x1A;
    g_ScratchPad.cells.halves[3] = -0xC0;
    g_ScratchPad.cells.halves[2] = radius;
    *shade                       = SELF(PartyMember)->timer * 3;
    g_ScratchPad.cells.halves[4] = -0x60;
    g_ScratchPad.cells.halves[5] = 0;
    wave                         = FIXED_MUL(rcos(((g_FrameCount + 4) & 0x3F) << 6), 0x80);
    inner.vx                     = (u32)(rsin(g_ScratchPad.cells.halves[7]) * g_ScratchPad.cells.halves[0]) >> 12;
    wave += FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]);
    inner.vy = wave;
    inner.vz = g_ScratchPad.cells.halves[3];
    wave     = FIXED_MUL(rcos(((g_FrameCount + 2) & 0x3F) << 6), 0x80);
    outer.vx = (u32)(rsin(g_ScratchPad.cells.halves[7]) * g_ScratchPad.cells.halves[1]) >> 12;
    wave += FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[1]);
    outer.vy = wave;
    outer.vz = g_ScratchPad.cells.halves[4];
    wave     = FIXED_MUL(rcos((g_FrameCount & 0x3F) << 6), 0x80);
    far.vx   = (u32)(rsin(g_ScratchPad.cells.halves[7]) * g_ScratchPad.cells.halves[2]) >> 12;
    wave += FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[2]);
    far.vy = wave;
    far.vz = g_ScratchPad.cells.halves[5];

    for (i = 1; i < 16; i++) {
        g_ScratchPad.cells.halves[7] = ((i + phase) & 0x3F) << 6;
        g_ScratchPad.cells.halves[0] += 13;
        g_ScratchPad.cells.halves[1] += 13;
        g_ScratchPad.cells.halves[2] += 13;
        g_ScratchPad.cells.halves[3] -= 0x40;
        g_ScratchPad.cells.halves[4] -= 0x40;
        g_ScratchPad.cells.halves[5] -= 0x40;
        g_ScratchPadVectors[0].vx = inner.vx;
        g_ScratchPadVectors[0].vy = inner.vy;
        g_ScratchPadVectors[0].vz = inner.vz;
        g_ScratchPadVectors[2].vx = outer.vx;
        g_ScratchPadVectors[2].vy = outer.vy;
        g_ScratchPadVectors[2].vz = outer.vz;
        wave                      = FIXED_MUL(rcos(((g_FrameCount + i + 4) & 0x3F) << 6), 0x80);
        g_ScratchPadVectors[1].vx = inner.vx = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]);
        wave += FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy = inner.vy = wave;
        g_ScratchPadVectors[1].vz = inner.vz = g_ScratchPad.cells.halves[3];
        wave                                 = FIXED_MUL(rcos(((g_FrameCount + i + 2) & 0x3F) << 6), 0x80);
        g_ScratchPadVectors[3].vx = outer.vx = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[1]);
        wave += FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vy = outer.vy = wave;
        g_ScratchPadVectors[3].vz = outer.vz = g_ScratchPad.cells.halves[4];
        prim                                 = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6]);
        setRGB3(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6]);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        setVector(&g_ScratchPadVectors[0], g_ScratchPadVectors[2].vx, g_ScratchPadVectors[2].vy, g_ScratchPadVectors[2].vz);
        setVector(&g_ScratchPadVectors[1], g_ScratchPadVectors[3].vx, g_ScratchPadVectors[3].vy, g_ScratchPadVectors[3].vz);
        setVector(&g_ScratchPadVectors[2], far.vx, far.vy, far.vz);
        wave                      = FIXED_MUL(rcos(((g_FrameCount + i) & 0x3F) << 6), 0x80);
        g_ScratchPadVectors[3].vx = far.vx = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[2]);
        wave += FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[3].vy = far.vy = wave;
        g_ScratchPadVectors[3].vz = far.vz = g_ScratchPad.cells.halves[5];
        prim                               = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}
#else
INCLUDE_ASM(func_801EF70C);
#endif

MATCH void func_801EFE48(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 5, 1, g_Self);
}

MATCH void func_801EFE8C(void) {
    s16* angle;

    SYS_DISPATCH_BYTE(D_801F0684, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        angle                          = &g_ScratchPad.cells.halves[7];
        *angle                         = ((SELF(PartyMember)->unk_09 * 3) & 0x3F) << 6;
        g_ScratchPad.cells.halves[0]   = SELF(PartyMember)->unk_0C + ((rsin((g_FrameCount & 0xF) << 6) * 16) >> 12);
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rcos(*angle) * g_ScratchPad.cells.halves[0]) >> 3);
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rsin(*angle) * g_ScratchPad.cells.halves[0]) >> 3);
        SELF(PartyMember)->pos.y.fixed += (rcos((g_FrameCount & 0x3F) << 6) * 128) >> 3;
        Battle_ProjectRange();
        func_801F01A4();
    }
}

MATCH void func_801F0018(void) {
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + SELF(PartyMember)->unk_14;
    SELF(PartyMember)->timer       = 0;
    SELF(PartyMember)->header.step++;
}

MATCH void func_801F0070(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->unk_09++;
    work = SELF(PartyMember);
    work->timer++;
    if (work->timer == 32) {
        work = SELF(PartyMember);
        work->header.step++;
    }
}

MATCH void func_801F00DC(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(unk_09, 1, 160);
}

MATCH void func_801F012C(void) {
    PartyMember* work;
    u8           count;

    work = SELF(PartyMember);
    work->unk_09++;
    work        = SELF(PartyMember);
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Actor_Clear();
    }
}

MATCH void func_801F01A4(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    g_ScratchPad.cells.halves[0] = 32;
    setXY4(prim, SELF(PartyMember)->screen_x.value + FIXED_MUL(rcos(3328), g_ScratchPad.cells.halves[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rsin(3328), g_ScratchPad.cells.halves[0]),
           SELF(PartyMember)->screen_x.value + FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]),
           SELF(PartyMember)->screen_x.value + FIXED_MUL(rcos(512), g_ScratchPad.cells.halves[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rsin(512), g_ScratchPad.cells.halves[0]),
           SELF(PartyMember)->screen_x.value + FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 0, 0, 31, 32);
    g_ScratchPad.cells.halves[6] = SELF(PartyMember)->timer * SELF(PartyMember)->param.unk_0B;
    setRGB0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6]);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_FT4));
}

/* func_801F0490 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F04F4 */
#include "overlays/bmagic/shared/Actor_Clear.h"

/* Sets the effect height to the mean z of the unblocked battlers on the side opposite the active battler. */
MATCH void func_801F0544(void) {
    s32 count;
    s32 sum;
    s32 i;

    count = 0;
    sum   = 0;
    if (g_Battle.active_battler < 3) {
        for (i = 0; i < 8; i++) {
            if (!Battle_SlotIsBlocked((u8)(i + 3))) {
                sum += g_BattleEnemyBattlers[i].pos.z.part.integer;
                count++;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!Battle_SlotIsBlocked((u8)i)) {
                sum += g_Game.members[i].pos.z.part.integer;
                count++;
            }
        }
    }
    SELF(PartyMember)->pos.z.part.integer = sum / count;
}
