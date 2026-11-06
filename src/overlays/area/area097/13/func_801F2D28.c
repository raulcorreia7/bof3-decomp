#include "area097_13.h"

MATCH s32 func_801F2D28(void) {
    if (Item_VitalHas(VITAL_ITEM_GUILD_LETTER)) {
        SYS_SetFlag(g_SaveData.scene_event_flags, 0x23);
    }
    return 0;
}
