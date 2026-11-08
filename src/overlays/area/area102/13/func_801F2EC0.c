#include "area102_13.h"

MATCH void func_801F2EC0(void) {
    func_801F2F44((g_Task)->timer >> 2);
    (g_Task)->timer -= 1;
    if ((g_Task)->timer < 8U) {
        (g_Task)->timer       = (g_Task)->unk_0A;
        (g_Task)->header.step = 1;
    }
}
