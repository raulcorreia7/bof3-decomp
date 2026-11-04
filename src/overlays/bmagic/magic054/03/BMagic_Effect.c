#include "magic054_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC2C(void) {
    BattleResultRings table;

    table = D_801EEC04;
    SYS_DISPATCH_TASK(table.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC98);

INCLUDE_ASM(func_801EF05C);

#include "shared/Effect_StartPlaying.h"

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

MATCH void func_801EF158(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF19C);

INCLUDE_ASM(func_801EF238);

INCLUDE_ASM(func_801EF3A4);

INCLUDE_ASM(func_801EF43C);

MATCH void func_801EF4A8(void) {
    PartyBattler* work;

    func_8014D978();
    work = g_SpadWork;
    work->unk_0C += work->unk_18;
    work->unk_10 += work->unk_1C;
    work->unk_40 += work->unk_0C;
    work->unk_44 += work->unk_10;
    if (work->unk_0C == 0xC00) {
        work->unk_02++;
    }
}

INCLUDE_ASM(func_801EF534);

MATCH void func_801EF624(void) {
    BMAGIC_TICK_EFFECT_WORK();
    func_801E5988();
}
