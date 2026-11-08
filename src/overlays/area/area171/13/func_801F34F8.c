#include "area171_13.h"

MATCH void func_801F34F8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Scene_StartEvent(SCENE_EVENT_SHOP_SAVE, 5);
        g_SceneEventSelection = 0xFF;
    }
}
