#include "area033_13.h"

MATCH void func_801F4544(void) {
    u8* scratch;
    s32 row_offset;
    s32 map_offset;

    if (g_Characters[0].character_id == 9 || (g_ScenarioState.flags_01 & 0x1) != 0) {
        Actor_Clear();
        return;
    }
    WorldMap_FindRegion();
    Area_SceneSelectRecord(0x205);

    SELF(Actor)->unk_48       = 0;
    SELF(Actor)->active_flags = 0;
    SELF(Actor)->mirror       = 0;
    ACTOR_CLEAR_TINT();

    scratch                                                  = SELF(u8);
    row_offset                                               = scratch[0x0B] * 4;
    map_offset                                               = D_801F4CC8[1 + row_offset] * g_AreaMapBundle.width;
    *(g_AreaCellCodes + map_offset + D_801F4CC8[row_offset]) = 0xA0;
    Script_Select(0);
    SELF(Actor)->header.mode = 1;
}
