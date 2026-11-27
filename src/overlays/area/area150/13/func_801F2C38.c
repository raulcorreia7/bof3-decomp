#include "area150_13.h"

/* func_801F2C38 */
MATCH void func_801F2C38(void) {
    g_UIMessageRequest = D_801F3804[g_UIMessageChoice];
    if (g_UIMessageChoice == 0) {
        if (Item_Add(ITEM_CATEGORY_ITEM, ITEM_WATER_JUG, 16 - (u16)Item_Count(ITEM_CATEGORY_ITEM, ITEM_WATER_JUG, 0), 0) != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        }
    }
}
