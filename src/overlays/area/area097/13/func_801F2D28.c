#include "area097_13.h"

MATCH s32 func_801F2D28(void) {
    if (Item_VitalHas(VITAL_ITEM_GUILD_LETTER)) {
        SYS_SetFlag(g_SceneEventFlags, 35);
    }
    return 0;
}
