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

MATCH void func_801EEF6C(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0xFF) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        g_SpadWork->step_01 += 1;
    }
}

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

MATCH void func_801EF6AC(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800AFC54();
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        g_SpadWork->step_01 += 1;
    }
}

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

MATCH void func_801EF9D4(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0xFF) {
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        func_800AEF98(4, 0);
        g_SpadWork->step_01 += 1;
    }
}

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

MATCH void func_801EFC90(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0xFF) {
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        func_800AEF98(4, 0);
        g_SpadWork->step_01 += 1;
    }
}

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

MATCH void func_801F0330(void) {
    g_SpadWork->unk_40              = 0x10000;
    g_SpadWork->unk_44              = 0x10000;
    g_SpadWork->unk_48              = 2;
    g_SpadWork->word_08.byte.unk_09 = 0x1E;
    g_SpadWork->unk_02 += 1;
}

INCLUDE_ASM(func_801F037C);

MATCH void func_801F03FC(void) {
    u8 counter;

    func_8014DAEC();
    counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        func_800A9820(g_BattleTargetSelector);
        func_800AFC98(2, 4);
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F047C(void) {
    if (func_8014DAEC() & 0xFF) {
        SND_QueueSelectionFx(0x101);
        g_SpadWork->word_08.byte.unk_09 = 0xF;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F04DC(void) {
    Actor* work;
    u8     timer;

    work         = g_SpadWork;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_40 = work->unk_40 - 0x800;
    work->unk_44 = work->unk_44 - 0x1000;
    if (timer == 0) {
        D_801EB4E0->word_08.byte.unk_0B = 0xFF;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F0548(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F0568);

INCLUDE_ASM(func_801F05FC);

MATCH void func_801F0710(void) {
    u8 count;

    g_SpadWork->unk_5D += 3;
    g_SpadWork->unk_5E += 3;
    g_SpadWork->unk_5F += 3;
    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (!(count & 0xFF)) {
        g_SpadWork->word_08.byte.unk_09 = func_800AFF98();
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F07D4(void) {
    u8 counter;

    func_8014DAEC();
    counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        func_800A9820(g_BattleTargetSelector);
        func_800AFC98(2, 4);
        g_SpadWork->word_08.byte.unk_09 = 0x20;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F0864(void) {
    if (func_8014DAEC() & 0xFF) {
        SND_QueueSelectionFx(0x101);
        g_SpadWork->word_08.byte.unk_09 = 0x20;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F08C4(void) {
    u8 counter;

    g_SpadWork->unk_5D -= 3;
    g_SpadWork->unk_5E -= 3;
    g_SpadWork->unk_5F -= 3;
    counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 0xFF;
        func_801E5988();
    }
}

MATCH void func_801F0964(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC84;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

MATCH void func_801F09D0(void) {
    g_SpadWork->word_08.byte.unk_09 = func_800AFF98();
    g_SpadWork->unk_02              = g_SpadWork->unk_02 + 1;
    func_8014D290();
}

MATCH void func_801F0A20(void) {
    u8 value;

    value                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = value;
    if (!(value & 0xFF)) {
        func_8014DAEC();
        func_800AFC98(2, 4);
        g_SpadWork->unk_02 += 1;
    } else if (func_8014DAEC() & 0xFF) {
        func_800AFC98(2, 4);
        g_SpadWork->word_08.byte.unk_09 = 0;
        g_SpadWork->unk_02 += 1;
    }
    func_8014D290();
}

MATCH void func_801F0AC8(void) {
    if (func_8014DAEC() & 0xFF) {
        func_800A9820(g_BattleTargetSelector);
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        g_SpadWork->unk_02 += 1;
    }
    func_8014D290();
}

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
    u8 value;

    if (g_FrameCount & 1) {
        g_SpadWork->coord_x_34.raw = D_801EB4E0->coord_x_34.raw;
        g_SpadWork->coord_y_38.raw = D_801EB4E0->coord_y_38.raw;
        func_8014DAEC();
        value                           = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = value;
        if (!(value & 0xFF)) {
            g_SpadWork->word_08.byte.unk_09 = g_SpadWork->word_08.byte.unk_0B + 4;
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

MATCH void func_801F11C4(void) {
    g_SpadWork->unk_5D -= 3;
    g_SpadWork->unk_5E -= 3;
    g_SpadWork->unk_5F -= 3;
    if ((s8)g_SpadWork->unk_5D == -0x80) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F1274(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F1294);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

MATCH void func_801F1384(void) {
    u8 temp_v0;

    func_8014DAEC();
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_800AFC98(2, 0);
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F1400(void) {
    if (func_8014DAEC() & 0xFF) {
        if (g_SpadWork->unk_02 == 5) {
            D_801EB4E0->word_08.byte.unk_0B = 0xFF;
        }
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801F1474);

MATCH void func_801F16E8(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F1708);

MATCH void Effect_ReloadTimerAndStep_801F17BC(void) {
    BMAGIC_RELOAD_TIMER_AND_STEP();
}

MATCH void func_801F1804(void) {
    u8 temp_v0;

    func_8014DAEC();
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_800AFC98(2, 0);
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F1880(void) {
    if (func_8014DAEC() & 0xFF) {
        if (g_SpadWork->unk_02 == 8) {
            D_801EB4E0->word_08.byte.unk_0B = 0xFF;
        }
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801F18F4);

MATCH void func_801F1BCC(void) {
    func_801E5988();
}
