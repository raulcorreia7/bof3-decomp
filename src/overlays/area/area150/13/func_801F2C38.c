#include "area150_13.h"

/* func_801F2C38 */
MATCH void func_801F2C38(void) {
    g_MessageRequest = D_801F3804[g_MessageChoice];
    if (g_MessageChoice == 0) {
        if (Item_Add(ITEM_CATEGORY_ITEM, ITEM_WATER_JUG, 16 - (u16)Item_Count(ITEM_CATEGORY_ITEM, ITEM_WATER_JUG, 0), 0) != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        }
    }
}
