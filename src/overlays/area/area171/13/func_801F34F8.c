#include "area171_13.h"

MATCH void func_801F34F8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Scene_StartEvent(SCENE_EVENT_INN, 5);
        g_SceneEventState.selection = 0xFF;
    }
}
