#include "area045_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */
MATCH void func_801F4610(void) {
    s32 row_offset;
    s32 map_offset;

    if (g_Characters[CHAR_INDEX_RYU].character_id == CHAR_ID_RYU_PAJAMAS || (g_ScenarioState.flags_01 & 0x1)) {
        Actor_Clear();
        return;
    }
    WorldMap_FindRegion();
    Area_SceneSelectRecord(0x205);

    SELF(Actor)->unk_48       = 0;
    SELF(Actor)->active_flags = 0;
    SELF(Actor)->mirror       = 0;
    ACTOR_CLEAR_TINT();

    row_offset                                               = SELF(Actor)->param.unk_0B * 4;
    map_offset                                               = D_801F4DA4[1 + row_offset] * g_AreaMapBundle.width;
    *(g_AreaCellCodes + map_offset + D_801F4DA4[row_offset]) = 0xA0;
    Script_Select(0);
    SELF(Actor)->header.mode = 1;
}
