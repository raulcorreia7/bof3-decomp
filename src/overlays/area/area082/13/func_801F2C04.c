#include "area082_13.h"

MATCH void func_801F2C04(void) {
    SYS_DISPATCH_BYTE(D_801F5734, g_Task->mode);
    if (g_Task->mode != 0) {
        func_801F3264();
    }
}
