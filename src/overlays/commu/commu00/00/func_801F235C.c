#include "commu00_00.h"

MATCH void func_801F235C(void) {
    if (EMI_IsReady()) {
        g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
        func_801F1684();
    }
}
