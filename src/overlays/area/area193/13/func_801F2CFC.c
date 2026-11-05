#include "area193_13.h"

MATCH void func_801F2CFC(void) {
    g_MessageRequest = D_801F3A10[D_801490C7];
    if (D_801490C7 == 1) {
        Item_Add(ITEM_CAT_ITEM, ITEM_WATER_JUG, 0x10 - (u16)Item_Count(ITEM_CAT_ITEM, ITEM_WATER_JUG, 0), 0);
        SND_PlayCue(EMI_CUE_ID(1, 6));
    }
}
