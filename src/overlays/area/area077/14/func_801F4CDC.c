#include "area077_14.h"
#include "area/spad.h"

MATCH void func_801F4CDC(void) {
    SYS_DISPATCH_BYTE(D_801F6250 + 0x34, g_Task->header.step);
}
