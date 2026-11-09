#include "area197_13.h"

MATCH s32 func_801F41F4(s32 entry_x, s32 entry_y) {
    if (D_80143F03 == 4) {
        if ((((entry_y == TO_COORD(112) + COORD_HALF) || (entry_y == TO_COORD(115) + COORD_HALF)) && (((entry_x >> 0x10) - 3) < 3U)) ||
            ((entry_x == TO_COORD(2) + COORD_HALF) && (((entry_y >> 0x10) - 113) < 3U)) || ((entry_x == TO_COORD(5) + COORD_HALF) && (((entry_y >> 0x10) - 113) < 3U))) {
            if (Item_VitalHas(VITAL_ITEM_CARD_KEY_B) != 0) {
                Scene_StartEvent(0x33, 0);
                return 1;
            }
        } else if (!((entry_x == TO_COORD(13) + COORD_HALF) && (((entry_y >> 0x10) - 113) < 2U) && (Item_VitalHas(VITAL_ITEM_CARD_KEY_B) == 0))) {
            return 0;
        }
        Game_SetScriptActive();
        D_80146874 = 5;
        D_80146875 = 0x14;
        return 1;
    }
    return 0;
}
