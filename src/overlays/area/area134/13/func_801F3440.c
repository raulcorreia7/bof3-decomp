#include "area134_13.h"

MATCH void func_801F3440(void) {
    Actor* actor;
    u8     step;

    actor      = g_Task;
    D_80146250 = &D_80146110;
    TASK_SET(&D_80146110);
    if (D_80146144 > 0x33FFFF) {
        D_80146865 = 0xFF;
        step       = 0x14;
    } else {
        D_80146865 = 0xFE;
        step       = 0x1E;
    }
    D_80146866 = 0;
    D_80146867 = 0;
    D_80146875 = step;
    TASK_SET(actor);
    func_80196070();
}
