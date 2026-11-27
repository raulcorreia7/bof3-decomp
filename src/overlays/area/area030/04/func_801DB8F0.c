#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Drives the AREA030 prompt row cursor from the pad pair and, when it
 * reaches the slot's row limit, queues the confirm cue and advances the panel
 * step. */
MATCH void func_801DB8F0(void) {
    s32 offset;

    if ((g_PadStates[0].pressed & PADRdown) != 0) {
        SELF(FishingState)->timer = g_Actors[g_FishingHookedFish].roll_90;
    } else {
        SELF(FishingState)->timer = (SELF(FishingState)->timer + 1);
    }

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, g_Actors[g_FishingHookedFish].unk_06);

    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(g_Actors[g_FishingHookedFish].unk_06, SELF(FishingState)->timer, 0);

    if (SELF(FishingState)->timer == g_Actors[g_FishingHookedFish].roll_90) {
        if (g_FishingNewRecord != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 13));
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SELF(FishingState)->timer     = 4;
        SELF(FishingState)->sub_index = (SELF(FishingState)->sub_index + 1);
    }
    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}
