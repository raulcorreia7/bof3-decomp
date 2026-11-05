#include "magic020_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC48(void) {
    BattleHandlerTable6 handlers = D_801EEC04;

    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EECC0);

INCLUDE_ASM(func_801EF0F8);

MATCH void func_801EF234(void) {
    u8 timer;

    func_801EFD88();
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = timer;
        if (timer == 0) {
            g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
        }
    }
}

MATCH void func_801EF2A8(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0xFF) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        func_800AEF98(4, 0);
        g_SpadWork->step_01 += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF398(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF3DC);

INCLUDE_ASM(func_801EF498);

MATCH void func_801EF518(void) {
    PartyBattler** selected;

    selected = &g_BattleSelectedActor;
    func_800AF2B4(*selected, 0x60);
    if (func_800AF66C(*selected, 0x20000)) {
        g_SpadWork->word_08.byte.unk_09         = func_800AFF98();
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 0xFF;
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF5A4(void) {
    u8 timer;

    func_8014DAEC();
    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF608(void) {
    if ((BATTLE_ACTIVE_WORK->word_08.byte.unk_0B == 0) && (func_8014DAEC() & 0xFF)) {
        g_SpadWork->word_08.byte.unk_09 = 0x10;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF678(void) {
    u8 temp_v0;

    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        s8 tone;

        g_SpadWork->flags_00 |= 0x20;
        g_SpadWork->unk_5C = 1;
        tone               = -0x40;
        g_SpadWork->unk_5D = tone;
        g_SpadWork->unk_5E = tone;
        g_SpadWork->unk_5F = tone;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF720);

MATCH void func_801EF7D0(void) {
    g_SpadWork->unk_5D += 0x10;
    g_SpadWork->unk_5E += 0x10;
    g_SpadWork->unk_5F += 0x10;
    if ((s8)g_SpadWork->unk_5D == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 0xFF;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF874(void) {
    func_801E5988();
}

MATCH void func_801EF894(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC3C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_8014D290();
    }
}

INCLUDE_ASM(func_801EF928);

INCLUDE_ASM(func_801EFA70);

MATCH void func_801EFAD4(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EFAF4);

INCLUDE_ASM(func_801EFBA0);

MATCH void func_801EFD10(void) {
    if (func_8014D978() & 0xFF) {
        if (g_SpadWork->word_08.byte.unk_0B == 7) {
            func_800A9820(g_BattleTargetSelector);
        }
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFD88);
