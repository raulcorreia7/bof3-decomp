#include "area077_14.h"

MATCH void func_801F40D4(void) {
    if (g_Task->vx % 30 == 0) {
        SND_PlayCue(0x20B);
    }
    if (g_Task->vx % 30 < 15) {
        func_801F4B80();
    }
    if (--g_Task->vx == 0) {
        func_80196070();
    }
}
