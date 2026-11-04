#include "area134_13.h"

/* func_801F5194 */
MATCH void Area_AddViewOffsetX2(void) {
    u16 count_;

    count_                 = g_AreaViewOffsetX;
    g_AreaViewRefreshCount = 2;
    g_AreaViewOffsetX      = (u16)(count_ + 2);
}
