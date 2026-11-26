#include "magic071_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_SparkleUpdate.h"

#include "overlays/bmagic/shared/BMagic_SparkleInit.h"

#include "overlays/bmagic/shared/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

/* Task mode 3: once fewer than EFFECT_SPARKLE_FEW_LEFT sparkles are alive, reloads the timer with 8 and advances header.mode. */
/* func_801EF15C */
MATCH void Effect_SparkleWait(void) {
    BMagic_AdvanceEffectStep(EFFECT_SPARKLE_FEW_LEFT);
}

#include "overlays/bmagic/shared/Effect_FadePaletteOut.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

#include "overlays/bmagic/shared/Effect_SparkleRunMode.h"

#include "overlays/bmagic/shared/Effect_SparkleStep.h"

#include "overlays/bmagic/shared/Effect_SparkleLaunch.h"

#include "overlays/bmagic/shared/Effect_SparkleGrow.h"

#include "overlays/bmagic/shared/Effect_SparkleFade.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawRays.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawWedges.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawDisc.h"

#include "overlays/bmagic/shared/Effect_SparkleAlloc.h"

#include "overlays/bmagic/shared/Effect_SparkleClear.h"
