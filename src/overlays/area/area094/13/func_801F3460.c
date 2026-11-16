#include "area094_13.h"

MATCH void func_801F3460(void) {
    if (g_GameLastAreaId == 0x79) {
        SYS_SetFlag(g_SceneEventFlags, 66);
        SYS_ClearFlag(g_SceneEventFlags, 67);
        Area_RunBundleObjects();
    }
}
