#include "area077_14.h"
#include "area/spad.h"

MATCH void func_801F4034(void) {
    SYS_DISPATCH_BYTE(D_801F6250 + 0x20, g_Task->header.mode);
}
