#include "area117_13.h"

MATCH void func_801F2E08(void) {
    s32 dx;
    s32 dy;
    s32 dy_next;

    if (g_AreaSceneMode != 0) {
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x200U);
        }
        ((Actor*)g_SpadWork)->state_02 = 2;
    }
    dx = 0xFFFD8000 + D_80145EC4;
    if (dx < 0) {
        dx = -dx;
    }
    if (dx <= 0x8000) {
        dy = 0xFFEB0000 + D_80145EC8;
        if (dy < 0) {
            dy = -dy;
        }
        if (dy > 0x10000) {
            dy_next = 0xFFEA0000 + D_80145EC8;
            if (dy_next < 0) {
                dy_next = -dy_next;
            }
            if (dy_next <= 0x10000) {
                goto trigger;
            }
        } else {
trigger:
            if (g_GameStateIndex == 0) {
                SND_PlayCue(0x200U);
            }
            ((Actor*)g_SpadWork)->state_02 = 2;
        }
    }
    func_801F314C();
}
