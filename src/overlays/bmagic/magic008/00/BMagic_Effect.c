#include "magic008_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EECF0(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EED5C);

INCLUDE_ASM(func_801EEF6C);

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF058(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF0B8);

INCLUDE_ASM(func_801EF324);

MATCH void func_801EF384(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF3F0);

INCLUDE_ASM(func_801EF6AC);

MATCH void Effect_StartPlaying_801EF728(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EF75C(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC30;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF7C8);

INCLUDE_ASM(func_801EF9D4);

MATCH void Effect_StartPlaying_801EFA40(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFA74(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC40;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFAD4);

INCLUDE_ASM(func_801EFC90);

MATCH void Effect_StartPlaying_801EFCFC(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFD30(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC4C;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFD90);

INCLUDE_ASM(func_801F0018);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH u32 func_801F0230(void) {
    return LOHU(g_BattleActionId) == 7 ? 7 : 0xFF;
}

MATCH void func_801F0250(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801F0294);

INCLUDE_ASM(func_801F0330);

INCLUDE_ASM(func_801F037C);

INCLUDE_ASM(func_801F03FC);

INCLUDE_ASM(func_801F047C);

INCLUDE_ASM(func_801F04DC);

MATCH void func_801F0548(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F0568);

INCLUDE_ASM(func_801F05FC);

INCLUDE_ASM(func_801F0710);

INCLUDE_ASM(func_801F07D4);

INCLUDE_ASM(func_801F0864);

INCLUDE_ASM(func_801F08C4);

MATCH void func_801F0964(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC84;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

MATCH void func_801F09D0(void) {
    g_SpadWork->unk_09 = func_800AFF98();
    g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    func_8014D290();
}

MATCH void func_801F0A20(void) {
    u8 temp_v0;

    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_8014DAEC();
        func_800AFC98(2, 4);
        goto block_4;
    }
    if (func_8014DAEC() & 0xFF) {
        func_800AFC98(2, 4);
        g_SpadWork->unk_09 = 0;
    block_4:
        g_SpadWork->unk_02 += 1;
    }
    func_8014D290();
}

INCLUDE_ASM(func_801F0AC8);

INCLUDE_ASM(func_801F0B44);

INCLUDE_ASM(func_801F0BBC);

MATCH void func_801F0DA8(void) {
    BmagicEffectFuncs handlers;

    handlers = D_801EEC94;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_8014D290();
    }
}

INCLUDE_ASM(func_801F0E54);

MATCH void func_801F0FA4(void) {
    u8 temp_v0;

    if (g_FrameCount & 1) {
        g_SpadWork->coord_x_34.raw = D_801EB4E0->coord_x_34.raw;
        g_SpadWork->coord_y_38.raw = D_801EB4E0->coord_y_38.raw;
        func_8014DAEC();
        temp_v0            = g_SpadWork->unk_09 - 1;
        g_SpadWork->unk_09 = temp_v0;
        if (!(temp_v0 & 0xFF)) {
            g_SpadWork->unk_09 = g_SpadWork->unk_0B + 4;
            g_SpadWork->unk_02 += 1;
        }
    } else {
        g_SpadWork->coord_x_34.raw = D_801EB4E0->coord_x_34.raw + g_SpadWork->unk_0C;
        g_SpadWork->coord_y_38.raw = D_801EB4E0->coord_y_38.raw + g_SpadWork->unk_10;
    }
}

INCLUDE_ASM(func_801F1090);

MATCH void func_801F117C(void) {
    if ((func_8014DAEC() & BYTE_MASK) != 0u) {
        g_SpadWork->unk_02 += 1u;
    }
}

INCLUDE_ASM(func_801F11C4);

MATCH void func_801F1274(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F1294);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

INCLUDE_ASM(func_801F1384);

INCLUDE_ASM(func_801F1400);

INCLUDE_ASM(func_801F1474);

MATCH void func_801F16E8(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F1708);

MATCH void Effect_ReloadTimerAndStep_801F17BC(void) {
    BMAGIC_RELOAD_TIMER_AND_STEP();
}

INCLUDE_ASM(func_801F1804);

INCLUDE_ASM(func_801F1880);

INCLUDE_ASM(func_801F18F4);

MATCH void func_801F1BCC(void) {
    func_801E5988();
}
