#include "game_00.h"

MATCH void func_8019BEFC(void) {
    Actor* work;
    u8     count;
    work  = g_Task;
    count = work->timer;
    if (count != 0) {
        work->timer = (count - 1);
    }
    if (g_AreaCameraMoving == 0) {
        work = g_Task;
        if (work->timer == 0) {
            work->header.mode = 1;
            func_8019BFD4();
        }
    }
    func_8014D978();
    Area_SetDrawMode();
}
