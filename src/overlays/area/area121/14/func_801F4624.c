#include "area121_14.h"

MATCH void func_801F4624(void) {
    /* Each access reloads the work cell: the stores go through its pointer, which
     * the compiler must assume may alias the cell. */
    s32 row_offset;
    s32 map_offset;

    if (g_Characters[CHAR_SLOT_RYU].character_id == CHAR_ID_RYU_PAJAMAS || (g_SceneState.flags_01 & 1)) {
        Actor_Clear();
        return;
    }
    Game_FindAreaHandler();
    Area_FindSceneRecord(0x205);

    g_Task->unk_48   = 0;
    g_Task->flags_24 = 0;
    g_Task->unk_2A   = 0;
    ACTOR_CLEAR_TINT();

    row_offset                                               = g_Task->unk_0B * 4;
    map_offset                                               = D_801F64E9[row_offset] * D_80104000;
    *(g_AreaCellCodes + map_offset + D_801F64E8[row_offset]) = 0xA0;
    Actor_SelectScript(0);
    g_Task->mode = 1;
}
