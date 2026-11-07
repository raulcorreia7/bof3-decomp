#include "area082_13.h"

MATCH void func_801F3D8C(void) {
    g_Task->timer++;
    if (g_Task->timer >= 0x11) {
        g_Task->timer = 0;
        SND_PlayCue(0x201U);
        g_Task->header.step++;
    }
    func_801F4430();
}
