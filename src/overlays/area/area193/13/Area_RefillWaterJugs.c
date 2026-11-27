#include "area193_13.h"

/* func_801F2CFC */
MATCH void Area_RefillWaterJugs(void) {
    g_UIMessageRequest = D_801F3A10[g_UIMessageChoice];
    if (g_UIMessageChoice == 1) {
        Item_Add(ITEM_CATEGORY_ITEM, ITEM_WATER_JUG, 16 - (u16)Item_Count(ITEM_CATEGORY_ITEM, ITEM_WATER_JUG, 0), 0);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    }
}
