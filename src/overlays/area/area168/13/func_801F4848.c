#include "area168_13.h"

MATCH void func_801F4848(void) {
    u16 message;

    if (g_MessageChoice == 0) {
        if (Item_VitalHas(VITAL_ITEM_CARD_KEY_A) != 0) {
            g_MessageRequest = AREA168_MESSAGE_ID_CHECK_PASSED;
            g_AreaSceneMode |= 1;
            return;
        }
        message = AREA168_MESSAGE_ID_CHECK_FAILED;
    } else {
        message = MESSAGE_NONE;
    }
    g_MessageRequest = message;
}
