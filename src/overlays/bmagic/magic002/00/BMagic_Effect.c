#include "magic002_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC78);

MATCH void func_801EEDE4(void) {
    if (D_801EC2E0->target.party->unk_09 >= 0x28) {
        g_Task->header.mode++;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEE64(void) {
    BMagic_DispatchTaskPair(func_801EEEBC, func_801EEF84);
}

MATCH void func_801EEEBC(void) {
    PartyMember* work;
    PartyMember* draw;

    work = g_Task;
    work->unk_14 += 0x100;
    work->unk_18 += 4;
    work->unk_0C += work->unk_1C;
    work->unk_09++;
    work->unk_10 += work->unk_20;
    draw = g_Task;
    func_801EF1FC(draw->unk_0C >> 16, draw->unk_10 >> 16, (draw->unk_18 << 15) >> 16, draw->unk_14, draw->unk_60,
                  draw->unk_58);
    if (g_Task->unk_09 >= 0xB) {
        g_Task->header.mode++;
    }
}

/* blocker: retail loads unk_09 before unk_60 and keeps g_Task in v1; first diff: lui v1 against a0 at 0x801EEF84. */
INCLUDE_ASM(func_801EEF84);

INCLUDE_ASM(func_801EF030);

INCLUDE_ASM(func_801EF1FC);
