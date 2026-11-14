#include "boss034_16.h"

MATCH void func_800C1B40(void) {
    g_Task->unk_20 += g_Task->timer;
    if (g_Task->unk_0C > 40) {
        g_Task->unk_0C--;
        if (g_FrameCount & 1) {
            g_Task->unk_1C++;
        }
    }
    if (g_Task->unk_10 > 40) {
        g_Task->unk_10 -= 1;
    }
    func_800C23D4((u16)g_Task->unk_20);
    if (g_FrameCount & 7) {
        g_Task->timer++;
    }
    if (g_Task->timer >= 64) {
        g_Task->unk_03++;
    }
}
