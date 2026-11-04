#include "area120_13.h"

MATCH void func_801F2CB4(void) {
    s16 timer;

    func_801F3630();
    func_801F3630();
    func_801F3630();
    func_801F3630();
    func_801F36B0();
    timer = g_SpadWork->unk_32 - 1;
    g_SpadWork->unk_32 = timer;
    if (timer == 0) {
        g_SpadWork->unk_06 = 1;
        g_SpadWork->unk_32 = 0x3C;
        g_SpadWork->unk_01++;
    }
}
