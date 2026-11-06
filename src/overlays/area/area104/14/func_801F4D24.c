#include "area104_14.h"

MATCH s32 func_801F4D24(void) {
    if ((g_GameAreaId != 0x79) ||
        !(func_801F4AE4(g_Task->x.fixed, g_Task->y.fixed, func_801BDE14(g_Task->x.fixed, g_Task->y.fixed, 1) & 0xFF) &
          0xFF)) {
        return 0;
    }
    func_801C24D0();
    g_Task->unk_09 -= 1;
    func_801B0DFC();
    g_GameState->mode_12B.s8_value = 1;
    g_Task->header.step            = 1;
    return 1;
}
