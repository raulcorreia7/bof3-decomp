#include "magic104_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    u8  slot;
    u32 i;

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (g_Battle.active_battler < 3) {
            SELF(PartyMember)->facing = g_BattleActiveActor->facing ^ 2;
        } else {
            SELF(PartyMember)->facing = g_BattleActiveActor->facing;
        }
    } else {
        if (g_Battle.active_battler < 3) {
            SELF(PartyMember)->facing = g_BattleActiveActor->facing;
        } else {
            SELF(PartyMember)->facing = g_BattleActiveActor->facing ^ 2;
        }
    }
    Battle_CenterCamera();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    for (i = 0; i < 8; i++) {
        slot                               = Battle_AllocEffect(1, 11);
        g_BattleEffects[slot].target.party = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = 0;
        g_BattleEffects[slot].unk_0A       = i * 2;
        SELF(PartyMember)->unk_0C          = D_801F08A8[i].x;
        SELF(PartyMember)->unk_10          = D_801F08A8[i].y;
        Effect_RotatePosition(g_Self);
        g_BattleEffects[slot].pos.x.fixed = g_AreaScrollTargetX + SELF(PartyMember)->unk_0C;
        g_BattleEffects[slot].pos.y.fixed = g_AreaScrollTargetY + SELF(PartyMember)->unk_10;
        g_BattleEffects[slot].pos.z.fixed = SELF(PartyMember)->pos.z.fixed;
        SND_SEQueueSelection(0x102);
    }
}

MATCH void func_801EEE7C(void) {
    if (SELF(PartyMember)->param.unk_0B == 7) {
        SELF(PartyMember)->unk_09 = 8;
        SELF(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEEC0(void) {
    u8  timer;
    u8  slot;
    u32 i;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->param.unk_0B = 0;
        SELF(PartyMember)->header.mode += 1;
        for (i = 0; i < 8; i++) {
            slot                               = Battle_AllocEffect(1, 11);
            g_BattleEffects[slot].target.party = SELF(PartyMember);
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].arg.unk_09   = 0;
            g_BattleEffects[slot].unk_0A       = i * 16 + 1;
            SELF(PartyMember)->unk_0C          = D_801F08A8[i].x;
            SELF(PartyMember)->unk_10          = D_801F08A8[i].y;
            Effect_RotatePosition(g_Self);
            g_BattleEffects[slot].pos.x.fixed = g_AreaScrollTargetX + SELF(PartyMember)->unk_0C;
            g_BattleEffects[slot].pos.y.fixed = g_AreaScrollTargetY + SELF(PartyMember)->unk_10;
            g_BattleEffects[slot].pos.z.fixed = SELF(PartyMember)->pos.z.fixed;
        }
    }
}

MATCH void func_801EF03C(void) {
    if (SELF(PartyMember)->param.unk_0B == 7) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EF09C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0E0(void) {
    SYS_DISPATCH_BYTE(D_801F08F0, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        func_801EFA54();
        func_801EFE34();
        func_801EFB2C();
        func_801EF370();
        PopMatrix();
    }
}

MATCH void func_801EF178(void) {
    s32 cue;
    u8  timer_next;

    timer_next               = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        cue = 0x100;
        if (SELF(PartyMember)->param.unk_0B & 0x1) {
            cue = 0x101;
        }
        SND_SEQueueSelection(cue);
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->timer  = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF21C(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 8) {
        SELF(PartyMember)->timer = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF27C(void) {
    u8 count;

    SELF(PartyMember)->timer += 1;
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        SELF(PartyMember)->timer = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF2F8(void) {
    PartyMember* work;
    PartyMember* active;

    work         = SELF(PartyMember);
    work->timer  = work->timer + 1;
    work         = SELF(PartyMember);
    work->unk_09 = work->unk_09 + 1;
    if (work->unk_09 == 0x18) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = SELF(PartyMember)->param.unk_0B;
        Effect_Reset();
    }
}

MATCH void func_801EF370(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      k;
    s32      i;
    s32      tpage;
    s32      x;
    s32      y;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 * 30;
    if (SELF(PartyMember)->header.step >= 2) {
        g_ScratchPad.cells.halves[0] = (SELF(PartyMember)->unk_09 - 8) * 15 + 240;
    }
    g_ScratchPad.cells.halves[2] = 24;
    if (SELF(PartyMember)->header.step >= 2) {
        g_ScratchPad.cells.halves[2] -= (SELF(PartyMember)->unk_09 - 8) / 2;
    }
    for (k = g_ScratchPad.cells.halves[2]; k > 16; k--) {
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(0), FIXED_MUL(rcos((k - 1) << 7), g_ScratchPad.cells.halves[0])),
                  FIXED_MUL(rcos(0), FIXED_MUL(rcos((k - 1) << 7), g_ScratchPad.cells.halves[0])), g_ScratchPadVectors[0].vz = (u32)(rsin((k - 1) << 7) * g_ScratchPad.cells.halves[0]) >> 12);
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(0), FIXED_MUL(rcos(k << 7), g_ScratchPad.cells.halves[0])), FIXED_MUL(rcos(0), FIXED_MUL(rcos(k << 7), g_ScratchPad.cells.halves[0])),
                  g_ScratchPadVectors[2].vz = (u32)(rsin(k << 7) * g_ScratchPad.cells.halves[0]) >> 12);
        for (i = 1; i <= 16; i++) {
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 8), FIXED_MUL(rcos((k - 1) << 7), g_ScratchPad.cells.halves[0]));
            g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 8), FIXED_MUL(rcos((k - 1) << 7), g_ScratchPad.cells.halves[0]));
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 8), FIXED_MUL(rcos(k << 7), g_ScratchPad.cells.halves[0]));
            g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 8), FIXED_MUL(rcos(k << 7), g_ScratchPad.cells.halves[0]));
            x                         = (g_ScratchPadVectors[3].vx << 9) + SELF(PartyMember)->pos.x.fixed;
            y                         = (g_ScratchPadVectors[3].vy << 9) + SELF(PartyMember)->pos.y.fixed;
            tpage                     = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            switch (SELF(PartyMember)->header.step) {
                case 1:
                    if (i < 8) {
                        setRGB0(prim, i * 16 + 80, (k - 16) * 8 + 1, (k - 16) * 8 + 1);
                        setRGB1(prim, i * 16 + 96, (k - 16) * 8 + 1, (k - 16) * 8 + 1);
                        setRGB2(prim, prim->r0, prim->g0, prim->b0);
                        setRGB3(prim, prim->r1, prim->g1, prim->b1);
                    } else {
                        setRGB0(prim, 208 - (i - 8) * 16, (k - 16) * 8 + 1, (k - 16) * 8 + 1);
                        setRGB1(prim, 224 - (i - 8) * 16, (k - 16) * 8 + 1, (k - 16) * 8 + 1);
                        setRGB2(prim, prim->r0, prim->g0, prim->b0);
                        setRGB3(prim, prim->r1, prim->g1, prim->b1);
                    }
                    break;
                case 2:
                    setRGB0(prim, 81 - SELF(PartyMember)->timer * 10, 17 - SELF(PartyMember)->timer * 2, 17 - SELF(PartyMember)->timer);
                    setRGB1(prim, prim->r0, prim->g0, prim->b0);
                    setRGB2(prim, 80, 16, 16);
                    setRGB3(prim, 80, 16, 16);
                    break;
                case 3:
                    setRGB0(prim, 1, 1, 1);
                    setRGB1(prim, 1, 1, 1);
                    setRGB2(prim, 81 - SELF(PartyMember)->timer * 10, 17 - SELF(PartyMember)->timer * 2, 17 - SELF(PartyMember)->timer * 2);
                    setRGB3(prim, prim->r2, prim->g2, prim->b2);
                    break;
            }
            Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
        }
    }
}

MATCH void func_801EFA54(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 0, 0, 0);
    if (SELF(PartyMember)->slot == 12) {
        rot.vz = (g_FrameCount & 0xF) << 8;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(SELF(PartyMember));
}

MATCH void func_801EFB2C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      x;
    s32      y;
    s32      radius;

    radius                       = rcos(0x800) * 30;
    g_ScratchPad.cells.halves[0] = radius * SELF(PartyMember)->unk_09 >> 12;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    for (i = 1; i <= 32; i++) {
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[0].vz = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz = 0;
        x                         = (g_ScratchPadVectors[2].vx >> 9) + SELF(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[2].vy >> 9) + SELF(PartyMember)->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        if (SELF(PartyMember)->header.step == 3) {
            g_ScratchPad.cells.halves[3] = 65 - SELF(PartyMember)->timer * 8;
            setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], 1);
        } else {
            setRGB0(prim, 64, 64, 1);
        }
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        Area_CellAddPrim(x, y, 2, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EFE34(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      radius;

    radius                       = rcos(0x800) * 34;
    g_ScratchPad.cells.halves[0] = radius * (SELF(PartyMember)->unk_09 + 1) >> 12;
    radius                       = rcos(0x800) * 34;
    g_ScratchPad.cells.halves[1] = radius * SELF(PartyMember)->unk_09 >> 12;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    for (i = 1; i <= 32; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz = 0;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[2].vz = 0;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vz = 0;
        if (SELF(PartyMember)->unk_09 > 8) {
            g_ScratchPad.cells.halves[3] = 33 - (SELF(PartyMember)->unk_09 - 8) * 2;
            setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
            setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        } else {
            setRGB0(prim, 32, 32, 32);
            setRGB1(prim, 32, 32, 32);
        }
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801F020C(void) {
    GFX_AddDitheredDrawMode(GFX_LAYER_BATTLE_SCENE, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    SYS_DISPATCH_BYTE(D_801F0900, SELF(PartyMember)->header.step);
    GFX_AddDitheredDrawMode(GFX_LAYER_BATTLE_SCENE, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
}

MATCH void func_801F02F4(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if (work->timer == 0) {
        work->unk_09 = 8;
        COORD_INT(work->pos.z) += 512;
        BMagic_NextStep();
    } else {
        work->timer = work->timer - 1;
    }
}

MATCH void func_801F034C(void) {
    PartyMember* work;
    u8           next;

    func_801EFA54();
    func_801F03C4();
    PopMatrix();
    work = SELF(PartyMember);
    next = work->unk_09 - 1;
    COORD_INT(work->pos.z) -= 64;
    work->unk_09 = next;
    if (next == 0) {
        g_BattleEffectBattler->param.unk_0B = SELF(PartyMember)->param.unk_0B;
        Effect_Reset();
    }
}

MATCH void func_801F03C4(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      band;
    s32      i;
    s32      tpage;
    s32      x;
    s32      y;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 * 8;
    for (band = 4; band < 12; band++) {
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), FIXED_MUL(rcos(band << 8), g_ScratchPad.cells.halves[0]));
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), FIXED_MUL(rcos(band << 8), g_ScratchPad.cells.halves[0]));
        g_ScratchPadVectors[1].vz = FIXED_MUL(rsin(band << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(0), FIXED_MUL(rcos((band + 1) << 8), g_ScratchPad.cells.halves[0]));
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(0), FIXED_MUL(rcos((band + 1) << 8), g_ScratchPad.cells.halves[0]));
        g_ScratchPadVectors[3].vz = FIXED_MUL(rsin((band + 1) << 8), g_ScratchPad.cells.halves[0]);
        for (i = 1; i <= 8; i++) {
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz;
            setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(i << 9), FIXED_MUL(rcos(band << 8), g_ScratchPad.cells.halves[0])),
                      FIXED_MUL(rcos(i << 9), FIXED_MUL(rcos(band << 8), g_ScratchPad.cells.halves[0])), FIXED_MUL(rsin(band << 8), g_ScratchPad.cells.halves[0]));
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz;
            setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(i << 9), FIXED_MUL(rcos((band + 1) << 8), g_ScratchPad.cells.halves[0])),
                      FIXED_MUL(rcos(i << 9), FIXED_MUL(rcos((band + 1) << 8), g_ScratchPad.cells.halves[0])), FIXED_MUL(rsin((band + 1) << 8), g_ScratchPad.cells.halves[0]));
            x     = (g_ScratchPadVectors[3].vx << 9) + SELF(PartyMember)->pos.x.fixed;
            y     = (g_ScratchPadVectors[3].vy << 9) + SELF(PartyMember)->pos.y.fixed;
            tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            setRGB0(prim, SELF(PartyMember)->unk_09 * 24 + 1, SELF(PartyMember)->unk_09 * 24 + 1, SELF(PartyMember)->unk_09 * 16 + 1);
            setRGB1(prim, prim->r0, prim->g0, prim->b0);
            setRGB2(prim, prim->r0, prim->g0, prim->b0);
            setRGB3(prim, prim->r0, prim->g0, prim->b0);
            Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
        }
    }
}
