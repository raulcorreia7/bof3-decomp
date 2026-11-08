#include "area104_14.h"
#include "area/map.h"

MATCH s32 func_801F4D24(void) {
    if ((g_GameAreaId != AREA_ID_STEEL_BEACH_MAP) ||
        !(func_801F4AE4(g_Task->pos.x.fixed, g_Task->pos.y.fixed,
                        func_801BDE14(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1) & 0xFF) &
          0xFF)) {
        return 0;
    }
    func_801C24D0();
    g_Task->timer -= 1;
    func_801B0DFC();
    g_Game.current->u.field.mode_12B.s8_value = 1;
    g_Task->header.step                       = 1;
    return 1;
}
