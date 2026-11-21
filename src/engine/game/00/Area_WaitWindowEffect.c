#include "game_00.h"

/* func_80198BC4 */
/* Runs area frames until the window effect is idle. */
MATCH void Area_WaitWindowEffect(u32 wait_steps) {
    u8 force_update;

    force_update = wait_steps;
    while (1) {
        SYS_ThreadWait(1);
        if (WINDOW_EFFECT_IDLE() && force_update == 0) {
            SYS_ThreadWait(1);
            break;
        }
        Area_RunFrame();
        if (WINDOW_EFFECT_IDLE()) {
            break;
        }
    }
}
