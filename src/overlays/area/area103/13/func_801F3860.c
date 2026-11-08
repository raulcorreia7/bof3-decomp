#include "area103_13.h"

MATCH void func_801F3860(void) {
    if (--TASK_BYTES[9] == 0) {
        func_80196070();
    } else {
        FIELD(u16, g_Task, 0x20) -= 0x200;
        FIELD(s32, g_Task, 0x24) += 0xFFF00000;
        ((void (*)(void*))func_801F38DC)(g_Task);
    }
}
