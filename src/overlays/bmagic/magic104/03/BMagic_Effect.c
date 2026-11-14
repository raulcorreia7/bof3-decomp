#include "magic104_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    u8  slot;
    u32 i;

    if (g_Battle.target_selector & 0x40) {
        if (g_Battle.active_battler < 3) {
            g_Task->facing = D_8014637C->facing ^ 2;
        } else {
            g_Task->facing = D_8014637C->facing;
        }
    } else {
        if (g_Battle.active_battler < 3) {
            g_Task->facing = D_8014637C->facing;
        } else {
            g_Task->facing = D_8014637C->facing ^ 2;
        }
    }
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 8; i++) {
        slot                               = Battle_AllocEffect(1, 11);
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = 0;
        g_BattleEffects[slot].unk_0A       = i * 2;
        g_Task->unk_0C                     = D_801F08A8[i].x;
        g_Task->unk_10                     = D_801F08A8[i].y;
        func_801DD350(g_Task);
        g_BattleEffects[slot].pos.x.fixed = g_AreaScrollTargetX + g_Task->unk_0C;
        g_BattleEffects[slot].pos.y.fixed = g_AreaScrollTargetY + g_Task->unk_10;
        g_BattleEffects[slot].pos.z.fixed = g_Task->pos.z.fixed;
        SND_QueueSelectionEffect(0x102);
    }
}

MATCH void func_801EEE7C(void) {
    if (g_Task->param.unk_0B == 7) {
        g_Task->unk_09 = 8;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEC0(void) {
    u8  timer;
    u8  slot;
    u32 i;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->param.unk_0B = 0;
        g_Task->header.mode += 1;
        for (i = 0; i < 8; i++) {
            slot                               = Battle_AllocEffect(1, 11);
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].arg.unk_09   = 0;
            g_BattleEffects[slot].unk_0A       = i * 16 + 1;
            g_Task->unk_0C                     = D_801F08A8[i].x;
            g_Task->unk_10                     = D_801F08A8[i].y;
            func_801DD350(g_Task);
            g_BattleEffects[slot].pos.x.fixed = g_AreaScrollTargetX + g_Task->unk_0C;
            g_BattleEffects[slot].pos.y.fixed = g_AreaScrollTargetY + g_Task->unk_10;
            g_BattleEffects[slot].pos.z.fixed = g_Task->pos.z.fixed;
        }
    }
}

MATCH void func_801EF03C(void) {
    if (g_Task->param.unk_0B == 7) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EF09C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0E0(void) {
    SYS_DISPATCH_BYTE(D_801F08F0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
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

    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        cue = 0x100;
        if (g_Task->param.unk_0B & 0x1) {
            cue = 0x101;
        }
        SND_QueueSelectionEffect(cue);
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF21C(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 8) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF27C(void) {
    u8 count;

    g_Task->timer += 1;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF2F8(void) {
    PartyMember* work;
    PartyMember* active;

    work         = g_Task;
    work->timer  = work->timer + 1;
    work         = g_Task;
    work->unk_09 = work->unk_09 + 1;
    if (work->unk_09 == 0x18) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = g_Task->param.unk_0B;
        func_801E5988();
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

    D_1F800000.view.effect.params[0] = g_Task->unk_09 * 30;
    if (g_Task->header.step >= 2) {
        D_1F800000.view.effect.params[0] = (g_Task->unk_09 - 8) * 15 + 240;
    }
    D_1F800000.view.effect.params[2] = 24;
    if (g_Task->header.step >= 2) {
        D_1F800000.view.effect.params[2] -= (g_Task->unk_09 - 8) / 2;
    }
    for (k = D_1F800000.view.effect.params[2]; k > 16; k--) {
        setVector(&D_1F800014[1], FIXED_MUL(rsin(0), FIXED_MUL(rcos((k - 1) << 7), D_1F800000.view.effect.params[0])),
                  FIXED_MUL(rcos(0), FIXED_MUL(rcos((k - 1) << 7), D_1F800000.view.effect.params[0])), D_1F800014[0].vz = (u32)(rsin((k - 1) << 7) * D_1F800000.view.effect.params[0]) >> 12);
        setVector(&D_1F800014[3], FIXED_MUL(rsin(0), FIXED_MUL(rcos(k << 7), D_1F800000.view.effect.params[0])), FIXED_MUL(rcos(0), FIXED_MUL(rcos(k << 7), D_1F800000.view.effect.params[0])),
                  D_1F800014[2].vz = (u32)(rsin(k << 7) * D_1F800000.view.effect.params[0]) >> 12);
        for (i = 1; i <= 16; i++) {
            D_1F800014[0].vx = D_1F800014[1].vx;
            D_1F800014[0].vy = D_1F800014[1].vy;
            D_1F800014[1].vx = FIXED_MUL(rsin(i << 8), FIXED_MUL(rcos((k - 1) << 7), D_1F800000.view.effect.params[0]));
            D_1F800014[1].vy = FIXED_MUL(rcos(i << 8), FIXED_MUL(rcos((k - 1) << 7), D_1F800000.view.effect.params[0]));
            D_1F800014[2].vx = D_1F800014[3].vx;
            D_1F800014[2].vy = D_1F800014[3].vy;
            D_1F800014[3].vx = FIXED_MUL(rsin(i << 8), FIXED_MUL(rcos(k << 7), D_1F800000.view.effect.params[0]));
            D_1F800014[3].vy = FIXED_MUL(rcos(i << 8), FIXED_MUL(rcos(k << 7), D_1F800000.view.effect.params[0]));
            x                = (D_1F800014[3].vx << 9) + g_Task->pos.x.fixed;
            y                = (D_1F800014[3].vy << 9) + g_Task->pos.y.fixed;
            tpage            = getTPage(1, 1, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
            switch (g_Task->header.step) {
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
                    setRGB0(prim, 81 - g_Task->timer * 10, 17 - g_Task->timer * 2, 17 - g_Task->timer);
                    setRGB1(prim, prim->r0, prim->g0, prim->b0);
                    setRGB2(prim, 80, 16, 16);
                    setRGB3(prim, 80, 16, 16);
                    break;
                case 3:
                    setRGB0(prim, 1, 1, 1);
                    setRGB1(prim, 1, 1, 1);
                    setRGB2(prim, 81 - g_Task->timer * 10, 17 - g_Task->timer * 2, 17 - g_Task->timer * 2);
                    setRGB3(prim, prim->r2, prim->g2, prim->b2);
                    break;
            }
            Area_AddCellPrim(x, y, 0, sizeof(POLY_G4));
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
    if (g_Task->slot == 12) {
        rot.vz = (g_FrameCount & 0xF) << 8;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
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

    radius                           = rcos(0x800) * 30;
    D_1F800000.view.effect.params[0] = radius * g_Task->unk_09 >> 12;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    for (i = 1; i <= 32; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[0].vz = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[1].vz = 0;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz = 0;
        x                = (D_1F800014[2].vx >> 9) + g_Task->pos.x.fixed;
        y                = (D_1F800014[2].vy >> 9) + g_Task->pos.y.fixed;
        tpage            = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        if (g_Task->header.step == 3) {
            D_1F800000.view.effect.params[3] = 65 - g_Task->timer * 8;
            setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], 1);
        } else {
            setRGB0(prim, 64, 64, 1);
        }
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        Area_AddCellPrim(x, y, 2, sizeof(POLY_G3));
    }
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EFE34(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      radius;

    radius                           = rcos(0x800) * 34;
    D_1F800000.view.effect.params[0] = radius * (g_Task->unk_09 + 1) >> 12;
    radius                           = rcos(0x800) * 34;
    D_1F800000.view.effect.params[1] = radius * g_Task->unk_09 >> 12;
    D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
    D_1F800014[3].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
    tpage                            = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    for (i = 1; i <= 32; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[0].vz = 0;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz = 0;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[2].vz = 0;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vz = 0;
        if (g_Task->unk_09 > 8) {
            D_1F800000.view.effect.params[3] = 33 - (g_Task->unk_09 - 8) * 2;
            setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
            setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        } else {
            setRGB0(prim, 32, 32, 32);
            setRGB1(prim, 32, 32, 32);
        }
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801F020C(void) {
    GFX_AddDitheredDrawMode(4, getTPage(0, 1, 320, 256));
    SYS_DISPATCH_BYTE(D_801F0900, g_Task->header.step);
    GFX_AddDitheredDrawMode(4, getTPage(0, 1, 320, 256));
}

MATCH void func_801F02F4(void) {
    PartyMember* work;

    work = g_Task;
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
    work = g_Task;
    next = work->unk_09 - 1;
    COORD_INT(work->pos.z) -= 64;
    work->unk_09 = next;
    if (next == 0) {
        g_BattleEffectBattler->param.unk_0B = g_Task->param.unk_0B;
        func_801E5988();
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

    D_1F800000.view.effect.params[0] = g_Task->unk_09 * 8;
    for (band = 4; band < 12; band++) {
        D_1F800014[1].vx = FIXED_MUL(rsin(0), FIXED_MUL(rcos(band << 8), D_1F800000.view.effect.params[0]));
        D_1F800014[1].vy = FIXED_MUL(rcos(0), FIXED_MUL(rcos(band << 8), D_1F800000.view.effect.params[0]));
        D_1F800014[1].vz = FIXED_MUL(rsin(band << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[3].vx = FIXED_MUL(rsin(0), FIXED_MUL(rcos((band + 1) << 8), D_1F800000.view.effect.params[0]));
        D_1F800014[3].vy = FIXED_MUL(rcos(0), FIXED_MUL(rcos((band + 1) << 8), D_1F800000.view.effect.params[0]));
        D_1F800014[3].vz = FIXED_MUL(rsin((band + 1) << 8), D_1F800000.view.effect.params[0]);
        for (i = 1; i <= 8; i++) {
            D_1F800014[0].vx = D_1F800014[1].vx;
            D_1F800014[0].vy = D_1F800014[1].vy;
            D_1F800014[0].vz = D_1F800014[1].vz;
            setVector(&D_1F800014[1], FIXED_MUL(rsin(i << 9), FIXED_MUL(rcos(band << 8), D_1F800000.view.effect.params[0])),
                      FIXED_MUL(rcos(i << 9), FIXED_MUL(rcos(band << 8), D_1F800000.view.effect.params[0])), FIXED_MUL(rsin(band << 8), D_1F800000.view.effect.params[0]));
            D_1F800014[2].vx = D_1F800014[3].vx;
            D_1F800014[2].vy = D_1F800014[3].vy;
            D_1F800014[2].vz = D_1F800014[3].vz;
            setVector(&D_1F800014[3], FIXED_MUL(rsin(i << 9), FIXED_MUL(rcos((band + 1) << 8), D_1F800000.view.effect.params[0])),
                      FIXED_MUL(rcos(i << 9), FIXED_MUL(rcos((band + 1) << 8), D_1F800000.view.effect.params[0])), FIXED_MUL(rsin((band + 1) << 8), D_1F800000.view.effect.params[0]));
            x     = (D_1F800014[3].vx << 9) + g_Task->pos.x.fixed;
            y     = (D_1F800014[3].vy << 9) + g_Task->pos.y.fixed;
            tpage = getTPage(1, 1, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
            setRGB0(prim, g_Task->unk_09 * 24 + 1, g_Task->unk_09 * 24 + 1, g_Task->unk_09 * 16 + 1);
            setRGB1(prim, prim->r0, prim->g0, prim->b0);
            setRGB2(prim, prim->r0, prim->g0, prim->b0);
            setRGB3(prim, prim->r0, prim->g0, prim->b0);
            Area_AddCellPrim(x, y, 0, sizeof(POLY_G4));
        }
    }
}
