#include "area047_13.h"
#include "area/spad.h"

MATCH void func_801F3448(void) {
    if (g_Task->header.step == 0) {
        g_Task->pos.x.fixed = -0x3900;
        g_Task->pos.y.fixed = -0x3880;
        g_Task->pos.z.fixed = -0x7F0;
        g_Task->header.step += 1;
    }
    func_801F34A0();
}
