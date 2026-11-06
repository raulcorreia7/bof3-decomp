#include "area045_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */
MATCH void func_801F4610(void) {
    s32 row_offset;
    s32 map_offset;

    if (g_Characters[CHAR_INDEX_RYU].character_id == CHAR_ID_RYU_PAJAMAS || (g_SceneState.flags_01 & 1)) {
        Actor_Clear();
        return;
    }
    Game_FindAreaHandler();
    Area_FindSceneRecord(0x205);

    TASK_BYTES[0x48]     = 0;
    g_Task->active_flags = 0;
    TASK_BYTES[0x2A]     = 0;
    TASK_BYTES[0x5D]     = 0;
    TASK_BYTES[0x5E]     = 0;
    TASK_BYTES[0x5F]     = 0;

    row_offset = TASK_BYTES[0x0B] * 4;
    map_offset = D_801F4D7C[0x29 + row_offset] * ((AreaMapBundle*)&D_80104000)->width_00;
    *(g_AreaCellCodes + map_offset + D_801F4D7C[0x28 + row_offset]) = 0xA0;
    Actor_SelectScript(0);
    TASK_BYTES[1] = 1;
}
