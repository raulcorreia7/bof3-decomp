#include "magic098_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEF84 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

INCLUDE_ASM(func_801EEFC8);

#include "overlays/bmagic/Effect_CountDownAndPickRandom.h"

/* enemy/party palette-fade arms share the func_800A9610(slot, 0x10) tail but retail keeps unk_03 in v1 and builds the row address in s0 from it. */
INCLUDE_ASM(func_801EF1B4);

/* func_801EF334 */
#include "overlays/bmagic/Effect_ReleaseTarget.h"

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF5D4);

INCLUDE_ASM(func_801EFE24);

INCLUDE_ASM(func_801F00C4);
