#include "magic086_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

MATCH void func_801EEC94(void) {
    PartyMember* actor;
    PartyMember* task;
    u8           slot;

    actor                                  = g_Battle.selected_actor;
    task                                   = g_Task;
    task->pos.x.fixed                      = actor->pos.x.fixed;
    task->pos.y.fixed                      = actor->pos.y.fixed;
    task->pos.z.fixed                      = actor->pos.z.fixed;
    slot                                   = Battle_AllocEffect(1, 29);
    g_BattleEffects[slot].target.party     = g_Task;
    g_BattleEffects[slot].header.mode      = 0;
    g_BattleEffects[slot].arg.unk_09       = 0;
    g_BattleEffects[slot].unk_0A           = 0;
    g_BattleEffects[slot].pos.x            = g_Task->pos.x;
    g_BattleEffects[slot].pos.y            = g_Task->pos.y;
    COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(g_Task->pos.z);
    slot                                   = Battle_AllocEffect(1, 29);
    g_BattleEffects[slot].target.party     = g_Task;
    g_BattleEffects[slot].header.mode      = 1;
    g_BattleEffects[slot].unk_0B           = 48;
    g_BattleEffects[slot].arg.unk_09       = 0;
    g_BattleEffects[slot].unk_0A           = 0;
    g_BattleEffects[slot].pos.x            = g_Task->pos.x;
    g_BattleEffects[slot].pos.y            = g_Task->pos.y;
    COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(g_Task->pos.z);
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
}

MATCH void func_801EEE44(void) {
    PartyMember* battler;

    battler = g_Battle.selected_actor;
    if (g_Task->param.unk_0B == 1) {
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 1, 1, 1, 0);
        g_Task->unk_09 = 0x10;
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_BrightenPalette.h"

MATCH void func_801EEFF0(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B == 2) {
        work->header.mode = (work->header.mode + 1);
    }
}

MATCH void func_801EF024(void) {
    PartyMember* battler;

    battler = g_Battle.selected_actor;
    g_PaletteFades[g_Task->timer].offset.red--;
    g_PaletteFades[g_Task->timer].offset.green--;
    g_PaletteFades[g_Task->timer].offset.blue--;
    if (g_PaletteFades[g_Task->timer].offset.red == 0) {
        func_80196718(battler);
        func_800AF814(g_Battle.target_selector);
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF278 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF2BC(void) {
    SYS_DISPATCH_BYTE(D_801F0360, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF424();
        PopMatrix();
    }
}

MATCH void func_801EF334(void) {
    g_Task->unk_09 += 1;
    g_Task->timer += 1;
    if (g_Task->unk_09 == 0x10) {
        BMagic_NextStep();
    }
}

MATCH void func_801EF3A0(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 2) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF3E0(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        func_801E5988();
    }
}

MATCH void func_801EF424(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000_WORD[0] = g_Task->timer * 12;
    D_1F800014[2].vx   = FIXED_MUL(rsin(0), D_1F800000_WORD[0]);
    D_1F800014[2].vy   = FIXED_MUL(rcos(0), D_1F800000_WORD[0]);

    for (i = 1; i <= 32; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 7), D_1F800000_WORD[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 7), D_1F800000_WORD[0]);
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        prim             = GFX_BeginPolyG3(1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_Task->unk_09 * 6, g_Task->unk_09 * 6, g_Task->unk_09 * 4);
        setRGB1(prim, g_Task->unk_09 * 4, g_Task->unk_09 * 4, g_Task->unk_09 * 2);
        setRGB2(prim, prim->r1, prim->g1, prim->b1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }

    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EF70C(void) {
    SYS_DISPATCH_BYTE(D_801F036C, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF9E0();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

MATCH void func_801EF7D4(void) {
    u8 count;

    g_Task->timer += 1;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x18) {
        g_BattleEffectBattler->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF850(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 22) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTickerAndStep.h"

MATCH void func_801EF8EC(void) {
    g_Task->unk_09 -= 1;
    g_Task->timer -= 1;
    if (g_Task->unk_09 == 0x10) {
        g_BattleEffectBattler->param.unk_0B = 2;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF974(void) {
    u8 count;
    u8 timer_next;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

/* Draws a ring of 64 semi-transparent Gouraud quads between the radii in scratch words 0 and 1. While the effect is
 * past its first step, the quads away from the two eighths that g_FrameCount picks become a green wall raised by
 * scratch word 3 and a sine wave, each one placed in its area cell. */
MATCH void func_801EF9E0(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;
    s32      spark;
    s32      next;
    s32      x;
    s32      y;
    s32      wave;

    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    if (g_Task->header.step != 0) {
        D_1F800000_WORD[0] = 0xC0;
    } else {
        D_1F800000_WORD[0] = g_Task->unk_09 * 12;
    }
    D_1F800000_WORD[1] = g_Task->unk_09 * 14;
    D_1F800000_WORD[3] = g_Task->timer << 4;
    spark              = g_FrameCount & 7;
    next               = (g_FrameCount + 1) & 7;
    D_1F800014[3].vx   = FIXED_MUL(rcos(0), D_1F800000_WORD[0]);
    D_1F800014[3].vy   = FIXED_MUL(rsin(0), D_1F800000_WORD[0]);
    D_1F800014[3].vz   = 0;
    for (i = 1; i <= 64; i++) {
        if ((i & 7) == spark || (i & 7) == next || g_Task->header.step == 0) {
            D_1F800014[0].vx = FIXED_MUL(rcos((i - 1) << 6), D_1F800000_WORD[1]);
            D_1F800014[0].vy = FIXED_MUL(rsin((i - 1) << 6), D_1F800000_WORD[1]);
            D_1F800014[0].vz = 0;
            D_1F800014[1].vx = FIXED_MUL(rcos(i << 6), D_1F800000_WORD[1]);
            D_1F800014[1].vy = FIXED_MUL(rsin(i << 6), D_1F800000_WORD[1]);
            D_1F800014[1].vz = 0;
            D_1F800014[2].vx = D_1F800014[3].vx;
            D_1F800014[2].vy = D_1F800014[3].vy;
            D_1F800014[2].vz = 0;
            D_1F800014[3].vx = FIXED_MUL(rcos(i << 6), D_1F800000_WORD[0]);
            D_1F800014[3].vy = FIXED_MUL(rsin(i << 6), D_1F800000_WORD[0]);
            D_1F800014[3].vz = 0;
        } else {
            wave             = ((i + g_FrameCount) & 0x1F) << 7;
            D_1F800014[0].vx = FIXED_MUL(rcos((i - 1) << 6), D_1F800000_WORD[0]);
            D_1F800014[0].vy = FIXED_MUL(rsin((i - 1) << 6), D_1F800000_WORD[0]);
            D_1F800014[0].vz = -(D_1F800000_WORD[3] + FIXED_MUL(rsin(wave), 32));
            D_1F800014[1].vx = FIXED_MUL(rcos(i << 6), D_1F800000_WORD[0]);
            D_1F800014[1].vy = FIXED_MUL(rsin(i << 6), D_1F800000_WORD[0]);
            D_1F800014[1].vz = -(D_1F800000_WORD[3] + FIXED_MUL(rsin(wave), 32));
            D_1F800014[2].vx = D_1F800014[3].vx;
            D_1F800014[2].vy = D_1F800014[3].vy;
            D_1F800014[2].vz = 0;
            D_1F800014[3].vx = D_1F800014[1].vx;
            D_1F800014[3].vy = D_1F800014[1].vy;
            D_1F800014[3].vz = 0;
            x                = (D_1F800014[3].vx << 9) + g_Task->pos.x.fixed;
            y                = (D_1F800014[3].vy << 9) + g_Task->pos.y.fixed;
            if (GetGraphType() == 1 || GetGraphType() == 2) {
                tpage = 0xA5;
            } else {
                tpage = 0x35;
            }
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        }
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        if ((i & 7) == spark || (i & 7) == next || g_Task->header.step == 0) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, g_Task->unk_09 * 2, g_Task->unk_09 * 2, g_Task->unk_09);
            setRGB3(prim, g_Task->unk_09 * 2, g_Task->unk_09 * 2, g_Task->unk_09);
            GFX_AddPrim(5, sizeof(POLY_G4));
        } else {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, 0x20, 0xC0, 0x20);
            setRGB3(prim, 0x20, 0xC0, 0x20);
            Area_AddCellPrim(x, y, 0, sizeof(POLY_G4));
        }
    }
    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801F0038(void) {
    SYS_DISPATCH_BYTE(D_801F0384, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F01A8();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

MATCH void func_801F0100(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_14 = 0x20;
        g_Task->unk_20 = -1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0154(void) {
    s32 dz;

    dz                       = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14           = dz;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) + dz;
    if (g_Task->unk_14 < -0x10) {
        func_801E5988();
    }
}

MATCH void func_801F01A8(void) {
    LINE_G3* prim;
    s32      tpage;
    long     depth;
    long     flag;

    D_1F800014[0].vx = D_1F800014[1].vx = D_1F800014[2].vx = rsin(g_Task->param.unk_0B << 9) >> 5;
    D_1F800014[0].vy = D_1F800014[1].vy = D_1F800014[2].vy = rcos(g_Task->param.unk_0B << 9) >> 5;
    D_1F800014[0].vz                                       = 32;
    D_1F800014[1].vz                                       = 24;
    D_1F800014[2].vz                                       = 0;
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (LINE_G3*)g_GfxPrimCursor;
    SetLineG3(prim);
    SetSemiTrans(prim, 1);
    RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    setRGB0(prim, 0x40, 0x40, 0x40);
    setRGB1(prim, 0xC0, 0x80, 0x80);
    setRGB2(prim, 1, 1, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(LINE_G3));
}
