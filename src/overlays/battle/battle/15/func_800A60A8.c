#include "battle_15.h"

/* @increments the global counter at g_Battle.ui_mode if g_UiPanelTasks[19].pos.vx equals 0xA3.
 */
MATCH void func_800A60A8(void) {
    s16*         state;
    volatile u8* counter;

    state = (s16*)&g_UiPanelTasks[19].pos.vx;
    if (*state == 0xA3) {
        counter  = &g_Battle.ui_mode;
        *counter = *counter + 1;
    }
}
