#include "area117_13.h"

MATCH void func_801F2E08(void) {
    if (g_AreaSceneMode != 0) {
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x200);
        }
        g_Task->header.step = 2;
    }

    if (abs(D_80145EC4 - TO_COORD_HALF(2)) <= COORD_HALF) {
        if (abs(D_80145EC8 - TO_COORD(0x15)) <= TO_COORD(1) || abs(D_80145EC8 - TO_COORD(0x16)) <= TO_COORD(1)) {
            if (g_GameStateIndex == 0) {
                SND_PlayCue(0x200);
            }
            g_Task->header.step = 2;
        }
    }

    func_801F314C();
}
