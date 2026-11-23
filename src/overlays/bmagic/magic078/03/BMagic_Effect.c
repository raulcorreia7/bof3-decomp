#include "magic078_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EECFC, Effect_PlayOnIdleTick};
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, tpage);

    SYS_DISPATCH_BYTE(handlers, TASK(PartyMember)->header.mode);

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, tpage);
}

MATCH void func_801EECFC(void) {
    PartyMember* actor;
    PartyMember* battler;
    u8           first;
    u8           slot;

    /* kept: retail rescales the slot index and re-reads g_BattleEffects at every store; a row
     * pointer changes the bytes. */
    actor                               = g_Battle.selected_actor;
    first                               = Battle_AllocEffect(1, 0xD);
    g_BattleEffects[first].target.party = TASK(PartyMember);
    g_BattleEffects[first].header.mode  = 0;
    g_BattleEffects[first].arg.unk_09   = 0;
    battler                             = g_BattleEffectBattler;
    g_BattleEffects[first].pos.x.fixed  = battler->pos.x.fixed;
    g_BattleEffects[first].pos.y.fixed  = battler->pos.y.fixed;
    g_BattleEffects[first].pos.z.fixed  = battler->pos.z.fixed + TO_COORD(512);
    slot                                = Battle_AllocEffect(1, 0xD);
    g_BattleEffects[slot].target.effect = &g_BattleEffects[first];
    g_BattleEffects[slot].unk_4C        = TASK(PartyMember);
    g_BattleEffects[slot].header.mode   = 1;
    g_BattleEffects[slot].arg.unk_09    = 0;
    g_BattleEffects[slot].pos.x.fixed   = actor->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed   = actor->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed   = actor->pos.z.fixed + TO_COORD(256);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_PlayOnIdleTick.h"

/* func_801EEEE4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF28(void) {
    s32 tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, tpage);

    if (TASK(PartyMember)->header.step < 3) {
        if ((g_FrameCount & BYTE_MASK) == 0x40) {
            TASK(PartyMember)->unk_0C = 0x1000;
        } else {
            TASK(PartyMember)->unk_0C = (g_FrameCount & 0x3F) << 6;
        }
    }

    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 2), TASK(PartyMember)->header.step);

    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        func_801EFEB8();
        func_801EF318();
        PopMatrix();
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, tpage);
}

MATCH void func_801EF08C(void) {
    u8 count;

    count = TASK(PartyMember)->unk_09;
    if ((count & BYTE_MASK) == 0xC) {
        TASK(PartyMember)->timer = 15;
        TASK(PartyMember)->header.step += 1;
        return;
    }
    TASK(PartyMember)->unk_09 = count + 1;
}

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

MATCH void func_801EF12C(void) {
    s32 angle;
    s32 target;
    s32 dir;

    angle = ratan2(g_Battle.selected_actor->pos.y.fixed - TASK(PartyMember)->pos.y.fixed, g_Battle.selected_actor->pos.x.fixed - TASK(PartyMember)->pos.x.fixed);
    dir   = TASK(PartyMember)->unk_0C;
    if (dir < 0) {
        dir += 0x3F;
    }
    dir >>= 6;
    target = angle & 0xFFF;
    if (target < 0) {
        target += 0x3F;
    }
    if (dir == (target >> 6)) {
        TASK(PartyMember)->timer = 15;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF1CC(void) {
    u8 count;

    count                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 1;
        TASK(PartyMember)->header.step   = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF228(void) {
    if (g_BattleEffectBattler->param.unk_0B == 2) {
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF278(void) {
    TASK(PartyMember)->timer += 8;
    if (TASK(PartyMember)->timer >= 129U) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF2CC(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

#ifdef NON_MATCHING
/* Draws the two leech rings and the centre quads and links both primitive runs into the map cell
 * by depth. */
NON_MATCHING void func_801EF318(void) {
    POLY_F4* prim;
    LINE_F4* line;
    u8*      base;
    u8*      line_base;
    s32      values[16];
    s32      line_values[12];
    s32*     azimuth;
    s32*     azimuth_next;
    long     depth;
    long     flag;
    s32      ring_base;
    s32      ring;
    s32      seg;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));

    base                        = g_GfxPrimCursor;
    line_base                   = base + 16 * sizeof(POLY_F4);
    line                        = (LINE_F4*)line_base;
    g_ScratchPad.cells.words[0] = TASK(PartyMember)->unk_09 * 10;
    g_ScratchPad.cells.words[1] = TASK(PartyMember)->unk_09 * 7;

    for (ring = 0; ring < 2; ring++) {
        ring_base                 = ring * 6;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rcos(D_801F08B8[ring]), g_ScratchPad.cells.words[1]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0x180), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[1].vz = FIXED_MUL(rsin(0x180), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[3].vx = FIXED_MUL(rcos(D_801F08B8[ring + 1]), g_ScratchPad.cells.words[1]);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(0x180), FIXED_MUL(rsin(D_801F08B8[ring + 1]), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[3].vz = FIXED_MUL(rsin(0x180), FIXED_MUL(rsin(D_801F08B8[ring + 1]), g_ScratchPad.cells.words[0]));
        for (seg = 1; seg < 7; seg++) {
            prim = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(prim);
            SetSemiTrans(prim, 1);

            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz;
            g_ScratchPadVectors[1].vx = FIXED_MUL(rcos(D_801F08B8[ring]), g_ScratchPad.cells.words[1]);
            g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(D_801F089C[seg]), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));
            g_ScratchPadVectors[1].vz = FIXED_MUL(rsin(D_801F089C[seg]), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));

            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz;
            g_ScratchPadVectors[3].vx = FIXED_MUL(rcos(D_801F08B8[ring + 1]), g_ScratchPad.cells.words[1]);
            g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(D_801F089C[seg]), FIXED_MUL(rsin(D_801F08B8[ring + 1]), g_ScratchPad.cells.words[0]));
            g_ScratchPadVectors[3].vz = FIXED_MUL(rsin(D_801F089C[seg]), FIXED_MUL(rsin(D_801F08B8[ring + 1]), g_ScratchPad.cells.words[0]));

            func_801EFE14(line, &line_values[seg - 1 + ring_base], g_ScratchPadVectors[0], g_ScratchPadVectors[1], g_ScratchPadVectors[3], g_ScratchPadVectors[2]);
            line++;
            values[ring_base + seg - 1] = RotAverage4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1,
                                                      (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);

            setRGB0(prim, 0x10, 0x10, 0x80);
            /* The flash brightens one segment per frame; from step 5 the segment fades with the timer. */
            if (TASK(PartyMember)->header.step == 3 && ((g_FrameCount & 0x1C) >> 2) == seg) {
                setRGB0(prim, 0x30, 0x30, 0x40);
            }
            if (TASK(PartyMember)->header.step >= 5) {
                setRGB0(prim, TASK(PartyMember)->timer + 0x10, 0x10, 0x80 - TASK(PartyMember)->timer);
            }
            g_GfxPrimCursor += sizeof(POLY_F4);
        }
    }

    for (ring = 0; ring < 4; ring += 2) {
        azimuth      = D_801F089C;
        azimuth_next = D_801F08A4;
        for (seg = 0; seg < 6; seg += 3) {
            prim = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(prim);
            SetSemiTrans(prim, 1);

            g_ScratchPadVectors[0].vx = FIXED_MUL(rcos(D_801F08B8[ring]), g_ScratchPad.cells.words[1]);
            g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(*azimuth), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));
            g_ScratchPadVectors[0].vz = FIXED_MUL(rsin(*azimuth), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));

            g_ScratchPadVectors[1].vx = FIXED_MUL(rcos(D_801F08B8[ring]), g_ScratchPad.cells.words[1]);
            g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(D_801F089C[seg + 3]), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));
            g_ScratchPadVectors[1].vz = FIXED_MUL(rsin(D_801F089C[seg + 3]), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));

            g_ScratchPadVectors[2].vx = FIXED_MUL(rcos(D_801F08B8[ring]), g_ScratchPad.cells.words[1]);
            g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(D_801F089C[seg + 1]), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));
            g_ScratchPadVectors[2].vz = FIXED_MUL(rsin(D_801F089C[seg + 1]), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));

            g_ScratchPadVectors[3].vx = FIXED_MUL(rcos(D_801F08B8[ring]), g_ScratchPad.cells.words[1]);
            g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(*azimuth_next), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));
            g_ScratchPadVectors[3].vz = FIXED_MUL(rsin(*azimuth_next), FIXED_MUL(rsin(D_801F08B8[ring]), g_ScratchPad.cells.words[0]));

            values[12 + (ring / 2) * 2 + seg / 3] = RotAverage4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1,
                                                                (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);

            setRGB0(prim, 1, 1, 0x80);
            if (TASK(PartyMember)->header.step >= 5) {
                setRGB0(prim, TASK(PartyMember)->timer + 1, 1, 0x80 - TASK(PartyMember)->timer);
            }
            azimuth += 3;
            azimuth_next += 3;
            g_GfxPrimCursor += sizeof(POLY_F4);
        }
    }

    func_800AF0F8(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, values, base, 16, sizeof(POLY_F4), 2);
    func_800AF0F8(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, line_values, line_base, 12, sizeof(LINE_F4), 2);
    g_GfxPrimCursor = (u8*)line;
}
#else
INCLUDE_ASM(func_801EF318);
#endif

MATCH void func_801EFE14(LINE_F4* prim, s32* out, SVECTOR v0, SVECTOR v1, SVECTOR v2, SVECTOR v3) {
    long p;
    long flag;

    SetLineF4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    setRGB0(prim, 0x40, 0x40, 0xC0);
    *out = RotAverage4(&v0, &v1, &v2, &v3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
}

MATCH void func_801EFEB8(void) {
    PartyMember* work;
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;

    PushMatrix();
    work = TASK(PartyMember);
    setVector(&rot, 0, 0, 0);
    if (work->slot == 13) {
        rot.vz = work->unk_0C;
    }
    setVector(&pos, (work->pos.x.fixed >> 9) - 0x4000, (work->pos.y.fixed >> 9) - 0x4000, -COORD_INT(work->pos.z) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

MATCH void func_801EFF84(void) {
    s32 tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, tpage);

    if (TASK(PartyMember)->header.step != 0) {
        BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F02FC);
    }

    SYS_DISPATCH_BYTE(D_801F08C4, TASK(PartyMember)->header.step);

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, tpage);
}

MATCH void func_801F00A0(void) {
    if (TASK(PartyMember)->unk_4C->param.unk_0B == 1) {
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F00EC */
MATCH void Effect_PlayCueAtTick(void) {
    u8 count;

    count = TASK(PartyMember)->unk_09;
    if ((count & BYTE_MASK) == 8) {
        SND_SEQueueSelection(0x101);
        TASK(PartyMember)->header.step += 1;
        return;
    }
    TASK(PartyMember)->unk_09 = count + 1;
}

MATCH void func_801F014C(void) {
    func_800AF2B4(g_BattleEffectBattler, 0x30);
    COORD_INT(TASK(PartyMember)->pos.z) = COORD_INT(TASK(PartyMember)->pos.z) + 0x10;
    if (func_800AF5FC(g_BattleEffectBattler, 0x1C000) != 0) {
        TASK(PartyMember)->timer = 30;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F01D0 */
MATCH void Effect_PlayCueOnTimeout(void) {
    PartyMember* work;

    work        = TASK(PartyMember);
    work->timer = work->timer - 1;
    if (work->timer == 0) {
        SND_SEQueueSelection(0x102);
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801F0230(void) {
    PartyMember* linked;

    linked = TASK(PartyMember)->unk_4C;
    func_800AF2B4(g_BattleEffectBattler, 8);
    if (func_800AF5FC(g_BattleEffectBattler, 0x4000) != 0) {
        linked->param.unk_0B     = 2;
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F02B4(void) {
    u8 timer;

    timer                    = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = timer;
    if (timer == 8) {
        Effect_Reset();
    }
}

/* Draws a sphere of 8 bands of 16 additive flat quads around the actor, radius four times byte 0x09;
 * from step 5 the quads fade with the timer. */
MATCH void func_801F02FC(void) {
    POLY_F4* prim;
    long     depth;
    long     flag;
    s32      ring;
    s32      i;
    s32      angle;
    s32      tpage;
    s32      x;
    s32      y;

    g_ScratchPad.cells.words[0] = TASK(PartyMember)->unk_09 << 2;
    for (ring = 0; ring < 8; ring++) {
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), FIXED_MUL(rcos((ring + 4) * 0x100), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), FIXED_MUL(rcos((ring + 4) * 0x100), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[1].vz = FIXED_MUL(rsin((ring + 4) * 0x100), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(0), FIXED_MUL(rcos((ring + 5) * 0x100), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(0), FIXED_MUL(rcos((ring + 5) * 0x100), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[3].vz = FIXED_MUL(rsin((ring + 5) * 0x100), g_ScratchPad.cells.words[0]);
        i                         = 1;
        do {
            angle                     = i << 8;
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz;
            setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(angle), FIXED_MUL(rcos((ring + 4) * 0x100), g_ScratchPad.cells.words[0])),
                      FIXED_MUL(rcos(angle), FIXED_MUL(rcos((ring + 4) * 0x100), g_ScratchPad.cells.words[0])), FIXED_MUL(rsin((ring + 4) * 0x100), g_ScratchPad.cells.words[0]));
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz;
            setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(angle), FIXED_MUL(rcos((ring + 5) * 0x100), g_ScratchPad.cells.words[0])),
                      FIXED_MUL(rcos(angle), FIXED_MUL(rcos((ring + 5) * 0x100), g_ScratchPad.cells.words[0])), FIXED_MUL(rsin((ring + 5) * 0x100), g_ScratchPad.cells.words[0]));
            x     = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.x.fixed;
            y     = (g_ScratchPadVectors[3].vy << 9) + TASK(PartyMember)->pos.y.fixed;
            tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
            prim = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(prim);
            PSX_SET_SEMI_TRANSPARENT(prim);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            if (TASK(PartyMember)->header.step < 5) {
                setRGB0(prim, 0x80, 0x10, 0x10);
            } else {
                setRGB0(prim, -127 - (TASK(PartyMember)->timer << 4), 17 - (TASK(PartyMember)->timer << 1), 17 - (TASK(PartyMember)->timer << 1));
            }
            Area_CellAddPrim(x, y, 2, sizeof(POLY_F4));
            i++;
        } while (i < 17);
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"
