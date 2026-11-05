#include "area104_14.h"

MATCH s32 func_801F50A8(void) {
    if ((g_GameFlags & 0x2000) != 0) {
        return 0;
    }
    if ((D_8014625C & D_80145ABA) == 0) {
        return 0;
    }
    D_80143BB0   = 4;
    g_Task->step = 0;
    return 1;
}
