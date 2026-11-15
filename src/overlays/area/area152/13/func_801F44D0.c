#include "area152_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F44D0(void) {
    s32 row_offset;
    s32 map_offset;

    if (g_Characters[CHAR_INDEX_RYU].character_id == CHAR_ID_RYU_PAJAMAS || (g_SceneState.flags_01 & 0x1)) {
        Actor_Clear();
        return;
    }
    Game_FindArea();
    Area_SelectSceneRecord(0x205);

    g_Task->unk_48       = 0;
    g_Task->active_flags = 0;
    g_Task->unk_2A       = 0;
    ACTOR_CLEAR_TINT();

    row_offset                                                     = g_Task->param.unk_0B * 4;
    map_offset                                                     = D_801F4C3C[0xD + row_offset] * MEM(u8, 0x80104000);
    *(g_AreaCellCodes + map_offset + D_801F4C3C[0xC + row_offset]) = 0xA0;
    Actor_SelectScript(0);
    g_Task->header.mode = 1;
}
