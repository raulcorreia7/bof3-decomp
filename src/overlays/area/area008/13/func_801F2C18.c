#include "area008_13.h"

MATCH void func_801F2C18(void) {
    SYS_DISPATCH_BYTE(g_AreaWorkStates, g_Task->header.mode);
}
