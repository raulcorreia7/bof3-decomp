#include "magic017_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC98);

INCLUDE_ASM(func_801EEF68);

MATCH void func_801EEFD8(void) {
    u16* flags;

    func_800AFC54();
    BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
    func_801E5988();
}

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF058);

INCLUDE_ASM(func_801EF11C);

INCLUDE_ASM(func_801EF248);

INCLUDE_ASM(func_801EF300);

INCLUDE_ASM(func_801EF460);

INCLUDE_ASM(func_801EF5FC);

MATCH void func_801EF694(void) {
    if (func_8014DAEC() != 0u) {
        g_SpadWork->word_08.byte.unk_09 = 8;
        g_SpadWork->unk_02              = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF6EC);

INCLUDE_ASM(func_801EF7E0);

INCLUDE_ASM(func_801EF8B4);

MATCH void func_801EF970(void) {
    func_801E5988();
}
