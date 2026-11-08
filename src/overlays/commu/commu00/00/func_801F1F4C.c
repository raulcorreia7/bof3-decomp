#include "commu00_00.h"

MATCH void func_801F1F4C(void) {
    if (EMI_IsReady() != 0) {
        g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
        func_801F1684();
        func_801F1638();
    }
}
