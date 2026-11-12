#include "game_00.h"

MATCH void func_80198B6C(void) {
    func_801990D0();
    func_80199308();
    if ((g_AreaCameraAngle.vx == -0x2AA) && (g_AreaCameraAngle.vz == 512)) {
        g_GameEntrySubstate = 0;
    }
}
