#include "sys/gameui.h"

/* Clears the message request and sets the game overlay state byte when the
 * menu choice is zero. One definition shared by the world area overlays; every
 * change here must verify every member. */
/* func_801F2C04 (area016), func_801F2C04 (area033), func_801F2C04 (area045), func_801F2C04 (area065), func_801F2C04 (area087), func_801F2C04 (area115), func_801F2C04 (area151), func_801F2C04 (area152), func_801F2C08 (area121), func_801F2C0C (area131), func_801F2C5C (area187), func_801F3764 (area088) */
MATCH void Message_ClearOnCancel(void) {
    if (MENU_SELECTION_IDLE()) {
        g_SaveData.scene_event.step = 2;
    }
    MESSAGE_REQUEST_CLEAR();
}
