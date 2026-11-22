#include "game_00.h"

MATCH void func_8019AD70(void) {
    Actor* work;

    work                = TASK(Actor);
    g_AreaCameraOffsetZ = work->vx;
    func_8019AAFC();
}
