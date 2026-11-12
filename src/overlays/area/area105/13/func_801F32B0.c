#include "area105_13.h"

MATCH void func_801F32B0(void) {
    if (D_80143F04 == AREA_ID_RHAPALA_WORLD_MAP) {
        if (D_80143F03 == 0) {
            SYS_SetFlag(g_SceneEventFlags, 79);
        }
        if (D_80143F03 == 1) {
            SYS_ClearFlag(g_SceneEventFlags, 79);
        }
    }
}
