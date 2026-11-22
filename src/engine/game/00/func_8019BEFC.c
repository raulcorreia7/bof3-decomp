#include "game_00.h"

MATCH void func_8019BEFC(void) {
    Actor* work;
    u8     count;
    work  = TASK(Actor);
    count = work->timer;
    if (count != 0) {
        work->timer = (count - 1);
    }
    if (g_AreaCameraMoving == 0) {
        work = TASK(Actor);
        if (work->timer == 0) {
            work->header.mode = 1;
            func_8019BFD4();
        }
    }
    Script_AnimStepLoop();
    Area_SetDrawMode();
}
