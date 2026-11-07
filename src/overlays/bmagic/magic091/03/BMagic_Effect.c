#include "magic091_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DrawActor.h"

/* blocker: call setup order; first diff: +0xF0 lui a0,0x8014 (retail loads the selector before li s0,1 and fills the delay slot with li a1,16) against li a1,16 first (candidate); body is magic055 func_801EECCC with handler 0x16 and func_800A9610 before the sound. */
INCLUDE_ASM(func_801EECCC);

#include "overlays/bmagic/func_801EEE3C.h"

#include "overlays/bmagic/Effect_DecayTimersAndPlay.h"

#include "overlays/bmagic/func_801EEF74.h"

/* func_801EEFFC */
#include "overlays/bmagic/Effect_FollowTarget.h"

#include "overlays/bmagic/func_801EF09C.h"

#include "overlays/bmagic/func_801EF124.h"

#include "overlays/bmagic/func_801EF1B8.h"

INCLUDE_ASM(func_801EF240);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF7B0);

INCLUDE_ASM(func_801EF9E4);
