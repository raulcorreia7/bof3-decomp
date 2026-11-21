#include "magic079_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EED38);
}

MATCH void func_801EEC5C(void) {
    u8           i;
    u32          slot;
    PartyMember* work;

    g_Task->param.unk_0B = 0;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 43) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = i;
        g_BattleEffects[slot].header.step  = 0;
        g_BattleEffects[slot].arg.unk_09   = 0x10;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B               = g_Task->param.unk_0B + 1;
    }
    SND_QueueSelectionSE(0x100);
    g_Task->header.mode = g_Task->header.mode + 1;
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EED98 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEDDC(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F02B4, func_801EF458);
}

MATCH void func_801EEE64(void) {
    g_Task->pos.x.fixed  = g_BattleSelectedActor->pos.x.fixed - 0x4000;
    g_Task->pos.y.fixed  = g_BattleSelectedActor->pos.y.fixed - 0x4000;
    g_Task->pos.z.fixed  = g_BattleSelectedActor->pos.z.fixed + 0x04000000;
    g_Task->param.unk_0B = 0x10;
    g_Task->unk_09       = 0x10;
    g_Task->timer        = 176;
    g_Task->header.step++;
}

MATCH void func_801EEEE4(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->pos.z.part.integer -= 0x40;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EEF34(void) {
    u8 count;
    u8 value;

    count = g_Task->unk_09;
    if ((count & BYTE_MASK) != 0x20) {
        g_Task->unk_09 = count + 1;
    }
    value         = g_Task->timer - 1;
    g_Task->timer = value;
    if ((value & BYTE_MASK) == 0x30) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EEFB8(void) {
    u8 count;
    u8 timer_next;

    count = g_Task->unk_09;
    if ((count & BYTE_MASK) != 0x20) {
        g_Task->unk_09 = count + 1;
    }
    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 16) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF048(void) {
    PartyMember* work;

    work               = g_Task;
    work->timer        = work->timer - 1;
    work               = g_Task;
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

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->pos.x.fixed  = D_8014637C->pos.x.fixed - 0x4000;
        g_Task->pos.y.fixed  = D_8014637C->pos.y.fixed - 0x4000;
        g_Task->pos.z.fixed  = D_8014637C->pos.z.fixed + 0x04000000;
        g_Task->param.unk_0B = 0x10;
        g_Task->unk_09       = 0x10;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF1DC(void) {
    PartyMember* work;
    u8           timer;

    work  = g_Task;
    timer = work->unk_09 - 1;
    COORD_INT(work->pos.z) -= 64;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09      = 0x20;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF23C(void) {
    u8 count;
    u8 value;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    value         = g_Task->timer + 1;
    g_Task->timer = value;
    if ((value & BYTE_MASK) == 0x80) {
        g_Task->unk_09 = 0x20;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF2BC(void) {
    u8 count;
    u8 timer_next;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    timer_next    = g_Task->timer + 1;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 160) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF348(void) {
    PartyMember* work;

    work               = g_Task;
    work->timer        = work->timer + 1;
    work               = g_Task;
    work->param.unk_0B = work->param.unk_0B - 1;
    if (work->param.unk_0B == 0) {
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EF458(void) {
}
#else
INCLUDE_ASM(func_801EF458);
#endif

MATCH void func_801EFBEC(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F035C, func_801F002C);
}

MATCH void func_801EFC74(void) {
    PartyMember* src;

    src                 = g_Battle.selected_actor;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 4;
    g_Task->timer       = 176;
    g_Task->header.step = g_Task->header.step + 1;
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

MATCH void func_801EFD2C(void) {
    g_Task->timer -= 1;
    if (g_BattleEffectBattler->param.unk_0B == g_Task->header.mode) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFD84(void) {
    PartyMember* work;
    PartyMember* active;

    work         = g_Task;
    work->timer  = work->timer - 1;
    work         = g_Task;
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

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        src                 = D_8014637C;
        g_Task->pos.x.fixed = src->pos.x.fixed;
        g_Task->pos.y.fixed = src->pos.y.fixed;
        g_Task->pos.z       = src->pos.z;
        g_Task->unk_09      = 4;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void Effect_CountUpAndStep2(void) {
    BMAGIC_COUNT_UP_AND_STEP();
}

MATCH void func_801EFF58(void) {
    g_Task->timer += 1;
    if (g_BattleEffectBattler->param.unk_0B == g_Task->header.mode) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFFB0(void) {
    PartyMember* work;
    PartyMember* active;

    work         = g_Task;
    work->timer  = work->timer + 1;
    work         = g_Task;
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
    g_ScratchPad.cells.halves[0] = g_Task->unk_09 << 4;
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
        shade                        = D_801F037C[g_Task->timer & 0xF];
        g_ScratchPad.cells.halves[4] = shade;
        setRGB0(prim, shade, 240, 240);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
