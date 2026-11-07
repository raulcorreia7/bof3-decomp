#include "area104_14.h"

MATCH s32 func_801F50A8(void) {
    if ((g_GameFlags & 0x2000) != 0) {
        return 0;
    }
    if ((D_8014625C & g_InputMasks[INPUT_SLOT_VIEW]) == 0) {
        return 0;
    }
    D_80143BB0          = 4;
    g_Task->header.step = 0;
    return 1;
}
