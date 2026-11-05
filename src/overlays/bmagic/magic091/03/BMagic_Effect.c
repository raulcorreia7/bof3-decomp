#include "magic091_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EECCC);

#include "overlays/bmagic/func_801EEE3C.h"

#include "overlays/bmagic/Effect_DecayTimersAndPlay.h"

#include "overlays/bmagic/func_801EEF74.h"

/* func_801EEFFC */
#include "overlays/bmagic/Effect_CopyBattlerCoordsOnTimerZero.h"

#include "overlays/bmagic/func_801EF09C.h"

MATCH void func_801EF124(void) {
    u8 temp_v0;

    g_SpadWork->word_08.byte.unk_0B += 1;
    g_SpadWork->word_08.byte.timer_0A -= 3;
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 2;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/func_801EF1B8.h"

INCLUDE_ASM(func_801EF240);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF7B0);

INCLUDE_ASM(func_801EF9E4);
