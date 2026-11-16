#include "magic137_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC7C);

#include "overlays/bmagic/Effect_CountDownTimerCallSelector.h"

MATCH void func_801EEF64(void) {
    if (g_Task->param.phase == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->unk_09 = 30;
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EEFD4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF018(void) {
    SYS_DISPATCH_BYTE(D_801F0104, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetFacingMatrix();
        func_801EF4C4();
        PopMatrix();
    }
}

MATCH void func_801EF090(void) {
    PartyMember* work;

    g_Task->unk_0C = -TO_COORD_HALF(2);
    g_Task->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    g_Task->pos.x.fixed        = VOL(s32, g_AreaScrollTargetX) + g_Task->unk_0C;
    g_Task->pos.y.fixed        = VOL(s32, g_AreaScrollTargetY) + g_Task->unk_10;
    g_Task->pos.z.part.integer = Area_SampleHeight(VOL(s32, g_AreaScrollTargetX), VOL(s32, g_AreaScrollTargetY)) + 0x200;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    work               = g_Task;
    work->param.unk_0B = 0x34;
    work->unk_14       = 0x2FFF;
    g_Task->unk_09     = 0;
    g_Task->timer      = 0x10;
    g_Task->header.step += 1;
}

MATCH void func_801EF174(void) {
    PartyMember* work = g_Task;
    u8           count;
    u8           phase = work->param.phase;
    u8           timer;
    phase += 1;
    timer             = work->unk_09;
    work->param.phase = phase + (timer >> 6);
    if (g_FrameCount & 0x1) {
        g_Task->timer += 1;
    }
    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if (count == 192) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF21C(void) {
    PartyMember* work = g_Task;
    u8           count;
    u8           phase = work->param.phase;
    u8           timer;
    phase += 1;
    timer             = work->unk_09;
    work->param.phase = phase + (timer >> 6);
    if (g_FrameCount & 0x1) {
        g_Task->timer -= 1;
    }
    count          = g_Task->unk_09 - 2;
    g_Task->unk_09 = count;
    if (count == 96) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_Drift.h"

#include "overlays/bmagic/Effect_SetFacingMatrix.h"

MATCH void func_801EF4C4(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;

    tpage = getTPage(1, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    D_1F800000.cells.halves[1] = 128;
    D_1F800000.cells.halves[0] = g_Task->unk_09;
    D_1F800000.cells.halves[2] = 128;
    D_1F800000.cells.halves[3] = g_Task->timer;
    D_1F800000.cells.halves[4] = (g_Task->param.unk_0B & 0x3F) << 6;
    setVector(&D_1F800014[0], FIXED_MUL(rsin(0x580), D_1F800000.cells.halves[2]), FIXED_MUL(rcos(0x580), D_1F800000.cells.halves[2]),
              FIXED_MUL(rsin(D_1F800000.cells.halves[4]), D_1F800000.cells.halves[3]));
    setVector(&D_1F800014[1], FIXED_MUL(rsin(0x280), D_1F800000.cells.halves[2]), FIXED_MUL(rcos(0x280), D_1F800000.cells.halves[2]),
              FIXED_MUL(rsin(D_1F800000.cells.halves[4]), D_1F800000.cells.halves[3]));
    for (i = 1; i < D_1F800000.cells.halves[0]; i++) {
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.cells.halves[2] = (i << 5) + 128;
        D_1F800000.cells.halves[4] = ((g_Task->param.unk_0B + i) & 0x3F) << 6;
        D_1F800014[2].vx           = D_1F800014[0].vx;
        D_1F800014[2].vy           = D_1F800014[0].vy;
        D_1F800014[2].vz           = D_1F800014[0].vz;
        D_1F800014[3].vx           = D_1F800014[1].vx;
        D_1F800014[3].vy           = D_1F800014[1].vy;
        D_1F800014[3].vz           = D_1F800014[1].vz;
        setVector(&D_1F800014[0], FIXED_MUL(rsin(0x580), D_1F800000.cells.halves[2]), FIXED_MUL(rcos(0x580), D_1F800000.cells.halves[2]),
                  FIXED_MUL(rsin(D_1F800000.cells.halves[4]), D_1F800000.cells.halves[3]));
        setVector(&D_1F800014[1], FIXED_MUL(rsin(0x280), D_1F800000.cells.halves[2]), FIXED_MUL(rcos(0x280), D_1F800000.cells.halves[2]),
                  FIXED_MUL(rsin(D_1F800000.cells.halves[4]), D_1F800000.cells.halves[3]));
        if (g_Task->header.step == 3) {
            D_1F800000.cells.halves[1] = (g_Task->unk_09 - 48) / 3 * 8;
        }
        GFX_SET_RGB_ALL(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
        if (i < 16) {
            setRGB0(prim, D_1F800000.cells.halves[1] / 16 * (i + 1), D_1F800000.cells.halves[1] / 16 * (i + 1), D_1F800000.cells.halves[1] / 16 * (i + 1));
            setRGB1(prim, prim->r0, prim->g0, prim->b0);
            setRGB2(prim, D_1F800000.cells.halves[1] / 16 * i, D_1F800000.cells.halves[1] / 16 * i, D_1F800000.cells.halves[1] / 16 * i);
            setRGB3(prim, prim->r2, prim->g2, prim->b2);
        }
        if (D_1F800000.cells.halves[0] - 8 < i) {
            D_1F800000.cells.halves[5] = D_1F800000.cells.halves[1];
            D_1F800000.cells.halves[1] = D_1F800000.cells.halves[1] / 8 * (D_1F800000.cells.halves[0] - i);
            setRGB0(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
            setRGB1(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
            D_1F800000.cells.halves[1] = D_1F800000.cells.halves[5] / 8 * (D_1F800000.cells.halves[0] - (i - 1));
            setRGB2(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
            setRGB3(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
        }
        prim->tpage                = GetTPage(1, 1, 832, 256);
        prim->clut                 = GetClut(0, 506);
        D_1F800000.cells.halves[7] = 252 - ((((g_FrameCount * 2) ^ 0xFFFF) + i) & 0x3F) * 4;
        if (D_1F800000.cells.halves[7] == 252) {
            D_1F800000.cells.halves[7] = 251;
        }
        setUV4(prim, 0, D_1F800000.cells.halves[7], 255, D_1F800000.cells.halves[7], 0, D_1F800000.cells.halves[7] + 4, 255, D_1F800000.cells.halves[7] + 4);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(2, sizeof(POLY_GT4));
    }
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
}

MATCH void func_801EFC58(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 2, g_Task);
    if (g_Task->header.flags != 0) {
        func_801EFDF8();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801EFDF8(void) {
    POLY_G4* prim;
    s32      tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    if (g_BattleEffectBattler->facing & 1) {
        setXYWH(prim, 0, 0, 319, 239);
    } else {
        setXY4(prim, 0x13F, 0, 0, 0, 0x13F, 0xEF, 0, 0xEF);
    }
    prim->r0 = prim->r3 = prim->g0 = prim->g3 = prim->b0 = prim->b3 = g_Task->unk_09;
    prim->r1 = prim->r2 = g_Task->unk_09 * 12;
    prim->g1 = prim->b1 = prim->g2 = prim->b2 = g_Task->unk_09 * 4;
    GFX_AddPrim(2, sizeof(POLY_G4));
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
}

#include "overlays/bmagic/Effect_DispatchStep.h"

MATCH void func_801F001C(void) {
    g_Task->param.phase = 0;
    g_Task->unk_09      = 0;
    Actor_SelectScript(3);
    Actor_StepAnimLoop();
    Area_AddActor();
    g_Task->header.step++;
}

#include "overlays/bmagic/Effect_AddActor.h"

MATCH void func_801F00D8(void) {
    Effect_Reset();
}
