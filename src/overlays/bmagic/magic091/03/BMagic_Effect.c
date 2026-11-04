#include "magic091_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EECCC);

#include "overlays/bmagic/func_801EEE3C.h"

/* Matches (204 bytes) with a u32 view of +0x08 tested against 0xFFFF0000 after two guarded byte
 * decrements (unk_09 under unk_0B < 4, unk_0A under unk_0B < 3) and the Effect_CountDownAndPlay
 * play statements; the view is a cast. Same bytes as magic055 func_801EEEA8. needs: type
 * PartyBattler+0x08 4 (2 sites). */
INCLUDE_ASM(func_801EEEA8);

#include "overlays/bmagic/func_801EEF74.h"

/* func_801EEFFC */
#include "overlays/bmagic/Effect_CopyBattlerCoordsOnTimerZero.h"

INCLUDE_ASM(func_801EF09C);

INCLUDE_ASM(func_801EF124);

INCLUDE_ASM(func_801EF1B8);

INCLUDE_ASM(func_801EF240);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF7B0);

INCLUDE_ASM(func_801EF9E4);
