#include "area105_13.h"

MATCH void func_801F32B0(void) {
    if (g_GameLastAreaId == AREA_ID_RHAPALA_WORLD_MAP) {
        if (g_GameCellType == 0) {
            SYS_SetFlag(g_SceneEventFlags, 79);
        }
        if (g_GameCellType == 1) {
            SYS_ClearFlag(g_SceneEventFlags, 79);
        }
    }
}
