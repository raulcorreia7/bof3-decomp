#include "area097_13.h"

MATCH s32 func_801F2C98(s32 x, s32 y) {
    u8 facing = g_BattlePartyBattlers[0].facing;

    if (y <= 0x3A0000 && ((x >> 16) - 0x30) < 3U) {
        if ((facing < 2U || facing == 2) && Item_VitalHas(VITAL_ITEM_GUILD_LETTER) == 0) {
            D_80146867                  = 1;
            g_SaveData.scene_event.mode = 0xD;
            g_SaveData.scene_event.step = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}
