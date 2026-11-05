#include "magic017_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC98);

#include "overlays/bmagic/Effect_ReleaseActiveBattlerOnTickerZero.h"

MATCH void func_801EEFD8(void) {
    u16* flags;

    func_800AFC54();
    BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
    func_801E5988();
}

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF058);

INCLUDE_ASM(func_801EF11C);

INCLUDE_ASM(func_801EF248);

INCLUDE_ASM(func_801EF300);

INCLUDE_ASM(func_801EF460);

MATCH void func_801EF5FC(void) {
    u8 counter;

    if (BATTLE_ACTIVE_WORK->word_08.byte.unk_0B == 1) {
        func_8014DAEC();
        counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = counter;
        if (!(counter & 0xFF)) {
            func_800A9820(g_BattleTargetSelector);
            func_800AFC98(2, 4);
            g_SpadWork->unk_02 += 1;
        }
    }
}

MATCH void func_801EF694(void) {
    if (func_8014DAEC() != 0u) {
        g_SpadWork->word_08.byte.unk_09 = 8;
        g_SpadWork->unk_02              = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF6EC(void) {
    s8 tone;
    u8 temp_v0;

    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        if ((u8)g_BattleActingBattler >= 3U) {
            func_801E257C(g_BattleActingBattler, 0);
        }
        g_SpadWork->flags_00 |= 0x20;
        g_SpadWork->unk_5C              = 1;
        g_SpadWork->unk_2B              = 1;
        tone                            = -0x40;
        g_SpadWork->unk_5D              = tone;
        g_SpadWork->unk_5E              = tone;
        g_SpadWork->unk_5F              = tone;
        g_SpadWork->word_08.byte.unk_09 = 8;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF7E0);

MATCH void func_801EF8B4(void) {
    u8 count;

    g_SpadWork->unk_5D += 8;
    g_SpadWork->unk_5E += 8;
    g_SpadWork->unk_5F += 8;
    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (!(count & 0xFF)) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF970(void) {
    func_801E5988();
}
