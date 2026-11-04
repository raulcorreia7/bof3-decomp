#include "magic002_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC78);

INCLUDE_ASM(func_801EEDE4);

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEE64(void) {
    Bmagic_DispatchTaskPair(func_801EEEBC, func_801EEF84);
}

MATCH void func_801EEEBC(void) {
    PartyBattler* work;
    PartyBattler* draw;

    work = g_SpadWork;
    work->unk_14 += 0x100;
    work->unk_18 += 4;
    work->unk_0C += work->unk_1C;
    work->word_08.byte.unk_09++;
    work->unk_10 += work->unk_20;
    draw = g_SpadWork;
    func_801EF1FC(draw->unk_0C >> 16, draw->unk_10 >> 16, (draw->unk_18 << 15) >> 16, (s16)draw->unk_14,
                  (s16)draw->unk_60, (s16)draw->unk_58);
    if (g_SpadWork->word_08.byte.unk_09 >= 0xB) {
        g_SpadWork->step_01++;
    }
}

INCLUDE_ASM(func_801EEF84);

INCLUDE_ASM(func_801EF030);

INCLUDE_ASM(func_801EF1FC);
