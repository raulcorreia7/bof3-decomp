#include "area077_14.h"

MATCH void func_801F57BC(void) {
    func_801F529C(3, D_801F62CC[g_Task->timer & 3], 3, 3);
    func_801F529C(7, D_801F62DC[g_Task->timer & 3], 6, 9);
    func_801F529C(7, D_801F62DC[g_Task->timer & 3] + 1, 6, 10);
    g_Task->timer++;
}
