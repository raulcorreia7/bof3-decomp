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
    if (g_SpadWork->unk_0B == 0) {
        timer              = g_SpadWork->unk_09 - 1;
        g_SpadWork->unk_09 = timer;
        if (timer == 0) {
            g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
        }
    }
}

INCLUDE_ASM(func_801EF2A8);

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF398(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF3DC);

INCLUDE_ASM(func_801EF498);

MATCH void func_801EF518(void) {
    PartyBattler** selected;

    selected = &g_BattleSelectedActor;
    func_800AF2B4(*selected, 0x60);
    if (func_800AF66C(*selected, 0x20000)) {
        g_SpadWork->unk_09 = func_800AFF98();
        D_801EB4E0->unk_0B = 0xFF;
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF5A4(void) {
    u8 timer;

    func_8014DAEC();
    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF608);

INCLUDE_ASM(func_801EF678);

INCLUDE_ASM(func_801EF720);

INCLUDE_ASM(func_801EF7D0);

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

INCLUDE_ASM(func_801EFD10);

INCLUDE_ASM(func_801EFD88);
