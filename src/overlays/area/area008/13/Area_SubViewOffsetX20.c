#include "area008_13.h"

/* func_801F4534 */
MATCH void Area_SubViewOffsetX20(void) {
    u16 count_;

    COUNTER_STEP(g_AreaViewOffsetX, g_AreaViewRefreshCount, count_, -)
}
