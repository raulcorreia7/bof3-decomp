#include "sys/gameui.h"

/* Clear the area request slot and, when the selection byte is clear, reset the
 * game-overlay state bytes. One definition shared by the world area overlays;
 * each overlay's image header names its reset variant in
 * AREA_RESET_VARIANT. Every change here must verify every member
 * address. */
/* func_801F2C48 (area001), func_801F2C48 (area023), func_801F3034 (area040), func_801F3634 (area166), func_801F3B08
   (area041), func_801F3B8C (area143), func_801F3FB0 (area117), func_801F4320 (area108), func_801F4808 (area168) */
MATCH void Message_ClearRequest(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        g_SceneEventMode      = 0xA;
        g_SceneEventStep      = 0;
        g_SceneEventSelection = AREA_RESET_VARIANT;
    }
}
