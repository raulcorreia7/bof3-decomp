#include "area016_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F4610(void) {
    s32 row;
    s32 map_offset;

    if (g_Characters[CHAR_INDEX_RYU].character_id == CHAR_ID_RYU_PAJAMAS || (g_SceneState.flags_01 & 0x1)) {
        Actor_Clear();
        return;
    }
    Game_FindAreaHandler();
    Area_SelectSceneRecord(0x205);

    g_Task->unk_48       = 0;
    g_Task->active_flags = 0;
    g_Task->unk_2A       = 0;
    ACTOR_CLEAR_TINT();

    row                                                 = g_Task->param.unk_0B;
    map_offset                                          = D_801F4DA0[row].y * g_AreaMapBundle.width;
    *(g_AreaCellCodes + map_offset + D_801F4DA0[row].x) = 0xA0;
    Actor_SelectScript(0);
    g_Task->header.mode = 1;
}
