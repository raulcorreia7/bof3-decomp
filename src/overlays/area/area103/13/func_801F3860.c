#include "area103_13.h"

extern void func_80196070(void);
extern void func_801F38DC(void);

MATCH void func_801F3860(void) {
    if (--TASK_BYTES[9] == 0) {
        func_80196070();
    } else {
        *(u16*)(TASK_BYTES + 0x20) -= 0x200;
        *(s32*)(TASK_BYTES + 0x24) += 0xFFF00000;
        func_801F38DC();
    }
}
