#include "magic069_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EEE30);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE90 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEED4(void) {
    s32 tpage;

    SYS_DISPATCH_BYTE(D_801F0504, g_Task->header.step);
    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, 0xC);
    if (g_Task->header.flags & 1) {
        if (g_Task->header.step != 0) {
            func_801EFF14();
            func_801EFC00();
        }
    }
    if (g_Task->header.flags & 1) {
        if (g_Task->header.step >= 3) {
            func_801F0104();
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
    GFX_AddPrim(3, 0xC);
}

MATCH void func_801EF034(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        dst              = g_Task;
        src              = g_BattleEffectBattler;
        dst->unk_0C      = 0xB;
        dst->unk_2E.half = src->unk_2E.half + 0x37;
        dst->unk_30.half = src->unk_30.half - 0x10;
        dst->unk_09      = 0;
        g_Task->timer    = 32;
        g_Task->header.step++;
    }
}

MATCH void func_801EF0C4(void) {
    s32 step_next;

    step_next      = g_Task->unk_0C - 1;
    g_Task->unk_0C = step_next;
    g_Task->unk_2E.half -= step_next;
    if (g_Task->unk_0C == 0) {
        if (g_Task->param.unk_0B == 0) {
            SND_QueueSelectionFx(0x103);
            g_Task->header.step += 1;
            return;
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF15C(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        func_801F0274();
        g_Task->param.unk_0B = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF1D0(void) {
    u8 value;
    u8 value2;

    if (g_Task->param.unk_0B != 0) {
        value          = g_Task->unk_09 + 4;
        g_Task->unk_09 = value;
        if ((value & BYTE_MASK) == 0x10) {
            g_Task->param.unk_0B = 0;
        }
    } else {
        value2         = g_Task->unk_09 - 2;
        g_Task->unk_09 = value2;
        if (!(value2 & BYTE_MASK)) {
            g_Task->param.unk_0B = 1;
        }
    }
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        SND_QueueSelectionFx(0x101);
        g_Task->unk_09 = 0x10;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF2AC(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer - 2;
    work->timer = next;
    if (next == 8) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        func_801E5988();
    }
}

MATCH void func_801EF30C(void) {
    SYS_DISPATCH_BYTE(D_801F0518, g_Task->header.step);
    GFX_AddDitheredDrawMode(3, getTPage(0, 1, 320, 256));
    if (g_Task->header.flags & 1 && g_Task->header.step != 0) {
        func_801EFF14();
        func_801EFC00();
    }
    GFX_AddDitheredDrawMode(3, GetGraphType() != 1 ? (GetGraphType() == 2 ? 0x25 : 0x15) : 0x25);
}

MATCH void func_801EF430(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        dst              = g_Task;
        src              = g_BattleEffectBattler;
        dst->unk_0C      = 0xB;
        dst->unk_2E.half = src->unk_2E.half - 0x37;
        dst->unk_30.half = src->unk_30.half - 0x10;
        dst->unk_09      = 0;
        g_Task->timer    = 32;
        g_Task->header.step++;
    }
}

MATCH void func_801EF4C0(void) {
    s32 count;

    count          = g_Task->unk_0C - 1;
    g_Task->unk_0C = count;
    g_Task->unk_2E.half += count;
    if (g_Task->unk_0C == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF520(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 10, 2, g_Task);
}

INCLUDE_ASM(func_801EF564);

INCLUDE_ASM(func_801EF724);

INCLUDE_ASM(func_801EF834);

MATCH void func_801EF9C4(void) {
    u8 timer;
    u8 counter;

    func_801EFA84();
    timer = g_Task->timer;
    if ((timer & BYTE_MASK) != 24) {
        g_Task->timer = timer + 4;
    }
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x14) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

INCLUDE_ASM(func_801EFA84);

INCLUDE_ASM(func_801EFC00);

INCLUDE_ASM(func_801EFF14);

MATCH void func_801F0104(void) {
    LINE_F2*      line;
    volatile u16* shade;

    shade      = &D_1F800006;
    line       = (LINE_F2*)g_GfxPrimCursor;
    *shade     = 0x80;
    D_1F80000C = g_Task->unk_2E.half;
    /* FAKE: retail stores each staged coordinate before loading the next. */
    FAKE_ORDER_FENCE();
    D_1F80000E = g_Task->unk_30.half;
    /* FAKE: retail keeps the argument move in the call's delay slot. */
    FAKE_ORDER_FENCE();
    SetLineF2(line);
    SetSemiTrans(line, 1);
    line->x0 = D_1F80000C - 4;
    /* FAKE: retail keeps each staged coordinate access in order. */
    FAKE_ORDER_FENCE();
    line->y0 = D_1F80000E;
    FAKE_ORDER_FENCE();
    line->x1 = D_1F80000C + 4;
    FAKE_ORDER_FENCE();
    line->y1 = D_1F80000E;
    line->r0 = *shade;
    line->g0 = *shade;
    line->b0 = *shade;
    GFX_AddPrim(3, sizeof(LINE_F2));
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 1);
    line->x0 = D_1F80000C;
    FAKE_ORDER_FENCE();
    line->y0 = D_1F80000E + 4;
    FAKE_ORDER_FENCE();
    line->x1 = D_1F80000C;
    FAKE_ORDER_FENCE();
    line->y1 = D_1F80000E - 4;
    line->r0 = *shade;
    line->g0 = *shade;
    line->b0 = *shade;
    GFX_AddPrim(3, sizeof(LINE_F2));
}

INCLUDE_ASM(func_801F0274);
