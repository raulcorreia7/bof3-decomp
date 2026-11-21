#include "engine/game/00/game_00.h"

/* func_80198C38 */
/* Runs menu frames until the window effect is idle. */
MATCH void UI_WindowWaitEffect(u8 wait_steps) {
    do {
        SYS_ThreadWait(1);
        if (WINDOW_EFFECT_IDLE() && wait_steps == 0) {
            SYS_ThreadWait(1);
            break;
        }
        Game_UpdateMenuFrame();
    } while (WINDOW_EFFECT_BUSY());
}
