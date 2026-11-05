#include "area118_13.h"

MATCH void func_801F3534(void) {
    g_Task->unk_30 -= 0x20;
    if ((s16)g_Task->unk_30 < -0xFF) {
        g_Task->step++;
    }
    func_801F381C(0);
}
