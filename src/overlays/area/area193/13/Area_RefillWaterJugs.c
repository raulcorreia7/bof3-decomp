#include "area193_13.h"

/* func_801F2CFC */
MATCH void Area_RefillWaterJugs(void) {
    g_MessageRequest = D_801F3A10[g_MessageChoice];
    if (g_MessageChoice == 1) {
        /* FAKE: retail calls Item_Add with s32 arguments, so the count is not narrowed to u8. */
        ((s32 (*)(s32, s32, s32, s32))Item_Add)(ITEM_CAT_ITEM, ITEM_WATER_JUG, 16 - (u16)Item_Count(ITEM_CAT_ITEM, ITEM_WATER_JUG, 0), 0);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    }
}
