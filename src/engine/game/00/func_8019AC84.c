#include "game_00.h"

MATCH void func_8019AC84(void) {
    Actor* work;

    func_8019A904();
    work     = g_Task;
    work->vy = ((work->vx - g_AreaCameraOffsetZ) << 0x10) / work->timer;
}
