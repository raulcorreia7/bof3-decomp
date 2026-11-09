#include "sys/gameui.h"

/* Clears the message request and sets the game overlay state bytes when the menu choice is zero. */
/* func_801F2C04 (area001), func_801F2C04 (area023), func_801F3074 (area040), func_801F36A0 (area032), func_801F3AC0
   (area141), func_801F3BCC (area143), func_801F3DBC (area041), func_801F40CC (area117), func_801F4360 (area108) */
MATCH void Message_Clear(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        g_SceneEventMode      = SCENE_EVENT_SHOP_SAVE;
        g_SceneEventStep      = 5;
        g_SceneEventSelection = 0xFF;
    }
}
