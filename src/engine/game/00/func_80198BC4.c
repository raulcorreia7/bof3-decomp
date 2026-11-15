#include "game_00.h"

MATCH void func_80198BC4(u32 wait_steps) {
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
