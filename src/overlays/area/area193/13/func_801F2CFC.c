#include "area193_13.h"

MATCH void func_801F2CFC(void) {
    g_MessageRequest = D_801F3A10[g_MessageChoice];
    if (g_MessageChoice == 1) {
        Item_Add(ITEM_CAT_ITEM, ITEM_WATER_JUG, 0x10 - (u16)Item_Count(ITEM_CAT_ITEM, ITEM_WATER_JUG, 0), 0);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    }
}
