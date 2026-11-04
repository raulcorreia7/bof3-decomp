#include "area008_13.h"

/* func_801F450C */
MATCH void Area_AddViewOffsetX20(void) {
    u16 count_;

    COUNTER_STEP(g_AreaViewOffsetX, g_AreaViewRefreshCount, count_, +)
}
