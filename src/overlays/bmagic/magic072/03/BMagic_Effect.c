#include "magic072_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED38);

MATCH void func_801EEFA4(void) {
    PartyBattler* temp_s0;
    u8            temp_v0;

    temp_s0            = g_BattleSelectedActor;
    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_80196718(temp_s0);
        g_SpadWork->unk_0A = func_8019651C(temp_s0, 0, 0, 0, 1);
        g_SpadWork->unk_09 = 8;
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EF04C);

#include "overlays/bmagic/Effect_NextStep.h"

INCLUDE_ASM(func_801EF1A4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/func_801EF33C.h"

INCLUDE_ASM(func_801EF380);

INCLUDE_ASM(func_801EF47C);

INCLUDE_ASM(func_801EF67C);

INCLUDE_ASM(func_801EF72C);

INCLUDE_ASM(func_801EF810);

INCLUDE_ASM(func_801EFA44);

INCLUDE_ASM(func_801EFCDC);

INCLUDE_ASM(func_801F0000);

#include "overlays/bmagic/func_801F006C.h"
