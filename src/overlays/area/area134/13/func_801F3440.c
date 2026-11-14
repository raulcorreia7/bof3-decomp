#include "area134_13.h"

extern s32   D_80146144;
extern void* D_80146250;

MATCH void func_801F3440(void) {
    Actor* actor;
    u8     v;

    actor      = g_Task;
    D_80146250 = &D_80146110;
    TASK_SET(&D_80146110);
    if (D_80146144 > 0x33FFFF) {
        D_80146865 = 0xFF;
        v          = 0x14;
    } else {
        D_80146865 = 0xFE;
        v          = 0x1E;
    }
    D_80146866 = 0;
    D_80146867 = 0;
    D_80146875 = v;
    TASK_SET(actor);
    func_80196070();
}
