#include "magic132_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EEDD0);

INCLUDE_ASM(func_801EEEF4);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

INCLUDE_ASM(func_801EF0A4);

MATCH void func_801EF114(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF158);

INCLUDE_ASM(func_801EF200);

MATCH void func_801EF324(void) {
    PartyBattler* work;
    u8            count;

    work = g_SpadWork;
    count = work->unk_09 - 1;
    work->unk_09 = count;
    work->coord_x_34.raw += work->unk_0C;
    work->coord_y_38.raw += work->unk_10;
    if (count == 0) {
        g_SpadWork->unk_02++;
    }
}

INCLUDE_ASM(func_801EF388);

INCLUDE_ASM(func_801EF3E0);

INCLUDE_ASM(func_801EF44C);

INCLUDE_ASM(func_801EF4A4);

INCLUDE_ASM(func_801EF5B0);

INCLUDE_ASM(func_801EF914);
