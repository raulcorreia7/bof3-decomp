#include "magic057_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC50 */
#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EECB0(void) {
    g_SpadWork->coord_x_34.raw = BATTLE_ACTIVE_WORK->coord_x_34.raw;
    g_SpadWork->coord_y_38.raw = BATTLE_ACTIVE_WORK->coord_y_38.raw;
    g_SpadWork->word_3C.word   = BATTLE_ACTIVE_WORK->word_3C.word;
    GFX_CopyPalette(0x1A);
    g_GfxPalettePending += 1;
    g_SpadWork->step_01 += 1;
}

MATCH void func_801EED2C(void) {
    BattleResultRings table;

    table = D_801EEC10;
    SYS_DISPATCH_TASK(table.handlers, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EED98);

MATCH void func_801EEE50(void) {
    PartyBattler* temp_s0;

    temp_s0    = g_SpadWork;
    g_SpadWork = D_801EC2E0->target.party;
    func_8014DAEC();
    g_SpadWork                        = temp_s0;
    temp_s0->word_08.byte.unk_09      = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
}

INCLUDE_ASM(func_801EEEB0);

MATCH void func_801EEFA4(void) {
    if (g_SpadWork->word_08.byte.unk_09 == g_SpadWork->word_08.byte.timer_0A) {
        g_SpadWork->step_01 += 1;
        g_SpadWork->unk_02 = 0;
    }
}

MATCH void func_801EEFEC(void) {
    u16* battle_flags;

    battle_flags = &g_BattleState;
    *battle_flags |= 4;
    func_800A9820(*(battle_flags = &g_BattleTargetSelector));
    func_801E5988();
}

MATCH void func_801EF02C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF08C);

INCLUDE_ASM(func_801EF134);

INCLUDE_ASM(func_801EF3C4);

MATCH void func_801EF528(void) {
    PartyBattler* work;

    work                        = (PartyBattler*)D_801EB4E0;
    work->word_08.byte.timer_0A = work->word_08.byte.timer_0A + 1;
    func_801E5988();
}

MATCH void func_801EF55C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC38;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

MATCH void func_801EF5BC(void) {
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = D_801EFADC[g_SpadWork->word_08.byte.unk_09];
    SND_QueueSelectionFx(256);
    g_SpadWork->unk_10 = 0;
    g_SpadWork->unk_02++;
}

INCLUDE_ASM(func_801EF620);

MATCH void func_801EF7A0(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->unk_10 >= -2) {
        work->unk_10--;
    } else {
        work->unk_03++;
    }
}

MATCH void func_801EF7E0(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->unk_10 < 0) {
        work->unk_10++;
    } else {
        work->unk_03--;
    }
}

MATCH void func_801EF81C(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF83C);

INCLUDE_ASM(func_801EF900);

INCLUDE_ASM(func_801EFA38);

MATCH void func_801EFABC(void) {
    func_801E5988();
}
