#include "area077_14.h"
#include "area/spad.h"

MATCH void func_801F5608(void) {
    SYS_DISPATCH_BYTE(D_801F6250 + 0x6C, g_Task->header.step);
}
