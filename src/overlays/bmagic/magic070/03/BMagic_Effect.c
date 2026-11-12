#include "magic070_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28_2.h"

#include "overlays/bmagic/func_801EED38.h"

#include "overlays/bmagic/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(5);
}

#include "overlays/bmagic/func_801EF1A4.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/func_801EF33C.h"

#include "overlays/bmagic/func_801EF380.h"

#include "overlays/bmagic/Effect_LaunchSparkle.h"

#include "overlays/bmagic/func_801EF67C.h"

#include "overlays/bmagic/func_801EF72C.h"

#include "overlays/bmagic/Effect_DrawSparkleRays.h"

#include "overlays/bmagic/Effect_DrawSparkleWedges.h"

INCLUDE_ASM(func_801EFCDC);

#include "overlays/bmagic/func_801F0000.h"

#include "overlays/bmagic/func_801F006C.h"
