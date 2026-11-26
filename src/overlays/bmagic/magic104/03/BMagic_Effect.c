#include "magic104_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    u8  slot;
    u32 i;

    if (g_Battle.target_selector & 0x40) {
        if (g_Battle.active_battler < 3) {
            TASK(PartyMember)->facing = g_BattleActiveActor->facing ^ 2;
        } else {
            TASK(PartyMember)->facing = g_BattleActiveActor->facing;
        }
    } else {
        if (g_Battle.active_battler < 3) {
            TASK(PartyMember)->facing = g_BattleActiveActor->facing;
        } else {
            TASK(PartyMember)->facing = g_BattleActiveActor->facing ^ 2;
        }
    }
    Battle_CenterCamera();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 8; i++) {
        slot                               = Battle_AllocEffect(1, 11);
        g_BattleEffects[slot].target.party = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = 0;
        g_BattleEffects[slot].unk_0A       = i * 2;
        TASK(PartyMember)->unk_0C          = D_801F08A8[i].x;
        TASK(PartyMember)->unk_10          = D_801F08A8[i].y;
        Effect_RotatePosition(g_Task);
        g_BattleEffects[slot].pos.x.fixed = g_AreaScrollTargetX + TASK(PartyMember)->unk_0C;
        g_BattleEffects[slot].pos.y.fixed = g_AreaScrollTargetY + TASK(PartyMember)->unk_10;
        g_BattleEffects[slot].pos.z.fixed = TASK(PartyMember)->pos.z.fixed;
        SND_SEQueueSelection(0x102);
    }
}

MATCH void func_801EEE7C(void) {
    if (TASK(PartyMember)->param.unk_0B == 7) {
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEEC0(void) {
    u8  timer;
    u8  slot;
    u32 i;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->param.unk_0B = 0;
        TASK(PartyMember)->header.mode += 1;
        for (i = 0; i < 8; i++) {
            slot                               = Battle_AllocEffect(1, 11);
            g_BattleEffects[slot].target.party = TASK(PartyMember);
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].arg.unk_09   = 0;
            g_BattleEffects[slot].unk_0A       = i * 16 + 1;
            TASK(PartyMember)->unk_0C          = D_801F08A8[i].x;
            TASK(PartyMember)->unk_10          = D_801F08A8[i].y;
            Effect_RotatePosition(g_Task);
            g_BattleEffects[slot].pos.x.fixed = g_AreaScrollTargetX + TASK(PartyMember)->unk_0C;
            g_BattleEffects[slot].pos.y.fixed = g_AreaScrollTargetY + TASK(PartyMember)->unk_10;
            g_BattleEffects[slot].pos.z.fixed = TASK(PartyMember)->pos.z.fixed;
        }
    }
}

MATCH void func_801EF03C(void) {
    if (TASK(PartyMember)->param.unk_0B == 7) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EF09C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0E0(void) {
    SYS_DISPATCH_BYTE(D_801F08F0, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
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

    timer_next               = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        cue = 0x100;
        if (TASK(PartyMember)->param.unk_0B & 0x1) {
            cue = 0x101;
        }
        SND_SEQueueSelection(cue);
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->timer  = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF21C(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 8) {
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF27C(void) {
    u8 count;

    TASK(PartyMember)->timer += 1;
    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF2F8(void) {
    PartyMember* work;
    PartyMember* active;

    work         = TASK(PartyMember);
    work->timer  = work->timer + 1;
    work         = TASK(PartyMember);
    work->unk_09 = work->unk_09 + 1;
    if (work->unk_09 == 0x18) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = TASK(PartyMember)->param.unk_0B;
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

    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 30;
    if (TASK(PartyMember)->header.step >= 2) {
        g_ScratchPad.cells.halves[0] = (TASK(PartyMember)->unk_09 - 8) * 15 + 240;
    }
    g_ScratchPad.cells.halves[2] = 24;
    if (TASK(PartyMember)->header.step >= 2) {
        g_ScratchPad.cells.halves[2] -= (TASK(PartyMember)->unk_09 - 8) / 2;
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
            x                         = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.x.fixed;
            y                         = (g_ScratchPadVectors[3].vy << 9) + TASK(PartyMember)->pos.y.fixed;
            tpage                     = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            switch (TASK(PartyMember)->header.step) {
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
                    setRGB0(prim, 81 - TASK(PartyMember)->timer * 10, 17 - TASK(PartyMember)->timer * 2, 17 - TASK(PartyMember)->timer);
                    setRGB1(prim, prim->r0, prim->g0, prim->b0);
                    setRGB2(prim, 80, 16, 16);
                    setRGB3(prim, 80, 16, 16);
                    break;
                case 3:
                    setRGB0(prim, 1, 1, 1);
                    setRGB1(prim, 1, 1, 1);
                    setRGB2(prim, 81 - TASK(PartyMember)->timer * 10, 17 - TASK(PartyMember)->timer * 2, 17 - TASK(PartyMember)->timer * 2);
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
    if (TASK(PartyMember)->slot == 12) {
        rot.vz = (g_FrameCount & 0xF) << 8;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(TASK(PartyMember));
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
    g_ScratchPad.cells.halves[0] = radius * TASK(PartyMember)->unk_09 >> 12;
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
        x                         = (g_ScratchPadVectors[2].vx >> 9) + TASK(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[2].vy >> 9) + TASK(PartyMember)->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        if (TASK(PartyMember)->header.step == 3) {
            g_ScratchPad.cells.halves[3] = 65 - TASK(PartyMember)->timer * 8;
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
    g_ScratchPad.cells.halves[0] = radius * (TASK(PartyMember)->unk_09 + 1) >> 12;
    radius                       = rcos(0x800) * 34;
    g_ScratchPad.cells.halves[1] = radius * TASK(PartyMember)->unk_09 >> 12;
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
        if (TASK(PartyMember)->unk_09 > 8) {
            g_ScratchPad.cells.halves[3] = 33 - (TASK(PartyMember)->unk_09 - 8) * 2;
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
    SYS_DISPATCH_BYTE(D_801F0900, TASK(PartyMember)->header.step);
    GFX_AddDitheredDrawMode(GFX_LAYER_BATTLE_SCENE, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
}

MATCH void func_801F02F4(void) {
    PartyMember* work;

    work = TASK(PartyMember);
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
    work = TASK(PartyMember);
    next = work->unk_09 - 1;
    COORD_INT(work->pos.z) -= 64;
    work->unk_09 = next;
    if (next == 0) {
        g_BattleEffectBattler->param.unk_0B = TASK(PartyMember)->param.unk_0B;
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

    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 8;
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
            x     = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.x.fixed;
            y     = (g_ScratchPadVectors[3].vy << 9) + TASK(PartyMember)->pos.y.fixed;
            tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            setRGB0(prim, TASK(PartyMember)->unk_09 * 24 + 1, TASK(PartyMember)->unk_09 * 24 + 1, TASK(PartyMember)->unk_09 * 16 + 1);
            setRGB1(prim, prim->r0, prim->g0, prim->b0);
            setRGB2(prim, prim->r0, prim->g0, prim->b0);
            setRGB3(prim, prim->r0, prim->g0, prim->b0);
            Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
        }
    }
}
