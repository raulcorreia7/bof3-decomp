#include "magic069_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EEE30};

    table[SP_REF(u8*, 0x44)[1]]();
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE90(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEED4);

MATCH void func_801EF034(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_SpadWork->word_08.byte.unk_09 == 0) {
        dst                               = g_SpadWork;
        src                               = D_801EB4E0;
        dst->unk_0C                       = 0xB;
        dst->unk_2E.half                  = src->unk_2E.half + 0x37;
        dst->unk_30.half                  = src->unk_30.half - 0x10;
        dst->word_08.byte.unk_09          = 0;
        g_SpadWork->word_08.byte.timer_0A = 0x20;
        g_SpadWork->unk_02++;
    }
}

INCLUDE_ASM(func_801EF0C4);

INCLUDE_ASM(func_801EF15C);

MATCH void func_801EF1D0(void) {
    u8 value;
    u8 value2;

    if (g_SpadWork->word_08.byte.unk_0B != 0) {
        value                           = g_SpadWork->word_08.byte.unk_09 + 4;
        g_SpadWork->word_08.byte.unk_09 = value;
        if ((value & 0xFF) == 0x10) {
            g_SpadWork->word_08.byte.unk_0B = 0;
        }
    } else {
        value2                          = g_SpadWork->word_08.byte.unk_09 - 2;
        g_SpadWork->word_08.byte.unk_09 = value2;
        if (!(value2 & 0xFF)) {
            g_SpadWork->word_08.byte.unk_0B = 1;
        }
    }
    if (D_801EB4E0->word_08.byte.unk_0B == 1) {
        SND_QueueSelectionFx(0x101);
        g_SpadWork->word_08.byte.unk_09 = 0x10;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF2AC(void) {
    PartyBattler* work;
    u8            next;

    work                        = g_SpadWork;
    next                        = work->word_08.byte.timer_0A - 2;
    work->word_08.byte.timer_0A = next;
    if (next == 8) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF30C);

MATCH void func_801EF430(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_SpadWork->word_08.byte.unk_09 == 0) {
        dst                               = g_SpadWork;
        src                               = D_801EB4E0;
        dst->unk_0C                       = 0xB;
        dst->unk_2E.half                  = src->unk_2E.half - 0x37;
        dst->unk_30.half                  = src->unk_30.half - 0x10;
        dst->word_08.byte.unk_09          = 0;
        g_SpadWork->word_08.byte.timer_0A = 0x20;
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF4C0(void) {
    s32 temp_v1;

    temp_v1 = g_SpadWork->unk_0C - 1;
    g_SpadWork->unk_0C = temp_v1;
    g_SpadWork->unk_2E.half += temp_v1;
    if (g_SpadWork->unk_0C == 0) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF520(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 10, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF564);

INCLUDE_ASM(func_801EF724);

INCLUDE_ASM(func_801EF834);

INCLUDE_ASM(func_801EF9C4);

MATCH void func_801EFA50(void) {
    BATTLE_ACTIVE_WORK->word_08.byte.unk_0B--;
    func_801E5988();
}

INCLUDE_ASM(func_801EFA84);

INCLUDE_ASM(func_801EFC00);

INCLUDE_ASM(func_801EFF14);

INCLUDE_ASM(func_801F0104);

INCLUDE_ASM(func_801F0274);
