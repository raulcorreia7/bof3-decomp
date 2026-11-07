#include "magic010_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

#include "overlays/bmagic/Effect_SelectTargetAndAdvance.h"

INCLUDE_ASM(func_801EED0C);

MATCH void func_801EEE20(void) {
    D_80145BD6[MAGIC010_TASK->timer].red_offset--;
    D_80145BD6[MAGIC010_TASK->timer].green_offset--;
    D_80145BD6[MAGIC010_TASK->timer].blue_offset--;
    if (--MAGIC010_TASK->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_BattleSelectedActor);
        func_800AF814(g_BattleTargetSelector);
        MAGIC010_TASK->header.mode++;
    }
}

#include "shared/Effect_PlayOnce.h"
