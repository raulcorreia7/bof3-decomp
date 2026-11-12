#include "area144_13.h"

MATCH void func_801F2C48(void) {
    u8* work;

    work            = (u8*)g_Task;
    work[6]         = g_AreaDrawFlags;
    g_AreaDrawFlags = AREA_DRAW_SORTED_RECORDS | 0x2 | AREA_DRAW_APPEND_ACTOR_PRIMITIVES | AREA_DRAW_APPEND_AREA_PRIMITIVES;
    func_801F2E18();
    D_801F4960 = 0;
    g_Task->header.mode++;
}
