#include "magic069_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EEE30};

    table[TASK_BYTES[1]]();
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE90(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

INCLUDE_ASM(func_801EEED4);

MATCH void func_801EF034(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_Task->unk_09 == 0) {
        dst              = g_Task;
        src              = g_BattleEffectBattler;
        dst->unk_0C      = 0xB;
        dst->unk_2E.half = src->unk_2E.half + 0x37;
        dst->unk_30.half = src->unk_30.half - 0x10;
        dst->unk_09      = 0;
        g_Task->timer    = 0x20;
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
        if ((value & 0xFF) == 0x10) {
            g_Task->param.unk_0B = 0;
        }
    } else {
        value2         = g_Task->unk_09 - 2;
        g_Task->unk_09 = value2;
        if (!(value2 & 0xFF)) {
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
    PartyBattler* work;
    u8            next;

    work        = g_Task;
    next        = work->timer - 2;
    work->timer = next;
    if (next == 8) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF30C);

MATCH void func_801EF430(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_Task->unk_09 == 0) {
        dst              = g_Task;
        src              = g_BattleEffectBattler;
        dst->unk_0C      = 0xB;
        dst->unk_2E.half = src->unk_2E.half - 0x37;
        dst->unk_30.half = src->unk_30.half - 0x10;
        dst->unk_09      = 0;
        g_Task->timer    = 0x20;
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
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 10, 2, g_Task);
}

INCLUDE_ASM(func_801EF564);

INCLUDE_ASM(func_801EF724);

INCLUDE_ASM(func_801EF834);

MATCH void func_801EF9C4(void) {
    u8 timer;
    u8 counter;

    func_801EFA84();
    timer = g_Task->timer;
    if ((timer & 0xFF) != 0x18) {
        g_Task->timer = timer + 4;
    }
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & 0xFF) == 0x14) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

INCLUDE_ASM(func_801EFA84);

INCLUDE_ASM(func_801EFC00);

INCLUDE_ASM(func_801EFF14);

INCLUDE_ASM(func_801F0104);

INCLUDE_ASM(func_801F0274);
