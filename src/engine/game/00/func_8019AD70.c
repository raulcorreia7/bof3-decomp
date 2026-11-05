#include "game_00.h"

MATCH void func_8019AD70(void) {
    Actor* work;

    work                = g_SpadWork;
    g_AreaCameraOffsetZ = work->vx;
    func_8019AAFC();
}
