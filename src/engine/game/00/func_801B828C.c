#include "game_00.h"

MATCH void func_801B828C(void) {
    g_AreaWalkFlags |= AREA_WALK_ENTRY_ACTIVE;
    Script_Request((g_Task->direction + 8));
    g_Task->timer  = 0;
    g_Task->unk_0A = 0;
    g_Task->unk_03 = (g_Task->unk_03 + 1);
}
