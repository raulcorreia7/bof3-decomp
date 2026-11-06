#include "area097_13.h"

MATCH s32 func_801F2C98(s32 x, s32 y) {
    u8 facing = g_BattlePartyBattlers[0].facing;

    if (y <= TO_COORD(58) && ((x >> 16) - 48) < 3U) {
        if ((facing < 2U || facing == FACING_UP_RIGHT) && Item_VitalHas(VITAL_ITEM_GUILD_LETTER) == 0) {
            D_80146867       = 1;
            g_SceneEventMode = 0xD;
            g_SceneEventStep = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}
