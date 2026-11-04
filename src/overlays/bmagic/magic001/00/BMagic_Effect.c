#include "magic001_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EECC4);

INCLUDE_ASM(func_801EEF34);

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEFD8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF01C);

INCLUDE_ASM(func_801EF0E8);

INCLUDE_ASM(func_801EF164);

INCLUDE_ASM(func_801EF1CC);

INCLUDE_ASM(func_801EF280);

MATCH void func_801EF324(void) {
    if (func_8014DAEC() != 0u) {
        func_801E257C(g_BattleActingBattler, 0xA);
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF37C);

INCLUDE_ASM(func_801EF408);

INCLUDE_ASM(func_801EF468);

INCLUDE_ASM(func_801EF518);

INCLUDE_ASM(func_801EF5CC);

INCLUDE_ASM(func_801EF688);

MATCH void func_801EF72C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC3C;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF78C);

INCLUDE_ASM(func_801EFA14);

MATCH void Effect_StartPlaying_801EFA84(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFAB8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFAFC);

INCLUDE_ASM(func_801EFBEC);

INCLUDE_ASM(func_801EFC54);

INCLUDE_ASM(func_801EFD28);

MATCH void func_801EFE38(void) {
    s32 value;
    u8  value2;
    u8  value3;

    g_SpadWork->coord_x_34.raw += (s32)(rsin(g_SpadWork->unk_0C) << 0xD) >> 0xC;
    g_SpadWork->coord_y_38.raw += (s32)(rcos(g_SpadWork->unk_0C) << 0xD) >> 0xC;
    value                            = g_SpadWork->unk_14 + g_SpadWork->unk_20;
    g_SpadWork->unk_14               = value;
    g_SpadWork->word_3C.half.span_3E = (u16)g_SpadWork->word_3C.half.span_3E + value;
    if ((u8)g_SpadWork->unk_09 < 8U) {
        value3 = g_SpadWork->unk_0A;
        if (value3 < 0x10U) {
            g_SpadWork->unk_0A = value3 + 1;
        }
    }
    value2             = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = value2;
    if (!(value2 & 0xFF)) {
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EFF28);

INCLUDE_ASM(func_801EFFCC);

INCLUDE_ASM(func_801F00A8);

INCLUDE_ASM(func_801F014C);

INCLUDE_ASM(func_801F0238);
