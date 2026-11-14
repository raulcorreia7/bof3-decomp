#include "game_00.h"

MATCH void func_80198C38(u8 wait_steps) {
    do {
        SYS_ThreadWait(1);
        if (WINDOW_EFFECT_IDLE() && wait_steps == 0) {
            SYS_ThreadWait(1);
            break;
        }
        Game_UpdateMenuFrame();
    } while (WINDOW_EFFECT_BUSY());
}
