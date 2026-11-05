#include "magic072_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED38);

MATCH void func_801EEFA4(void) {
    PartyBattler* battler;
    u8            value;

    battler                         = g_BattleSelectedActor;
    value                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = value;
    if (!(value & 0xFF)) {
        func_80196718(battler);
        g_SpadWork->word_08.byte.timer_0A = func_8019651C(battler, 0, 0, 0, 1);
        g_SpadWork->word_08.byte.unk_09   = 8;
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

#include "overlays/bmagic/func_801EF67C.h"

#include "overlays/bmagic/func_801EF72C.h"

INCLUDE_ASM(func_801EF810);

INCLUDE_ASM(func_801EFA44);

INCLUDE_ASM(func_801EFCDC);

INCLUDE_ASM(func_801F0000);

#include "overlays/bmagic/func_801F006C.h"
