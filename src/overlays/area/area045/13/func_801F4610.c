#include "area045_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */
MATCH void func_801F4610(void) {
    s32 row_offset;
    s32 map_offset;

    if (g_Characters[CHAR_SLOT_RYU].character_id == CHAR_ID_RYU_PAJAMAS || (D_80146871 & 1)) {
        Actor_Clear();
        return;
    }
    Game_FindAreaHandler();
    Area_FindSceneRecord(0x205);

    g_SpadWork->unk_48 = 0;
    g_SpadWork->flags_24 = 0;
    g_SpadWork->unk_2A = 0;
    g_SpadWork->tint.bytes.unk_5D = 0;
    g_SpadWork->tint.bytes.unk_5E = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;

    row_offset = g_SpadWork->unk_0B * 4;
    map_offset = ((u8*)D_801F4D7C + 0x29)[row_offset] * ((AreaMapBundle*)&D_80104000)->width_00;
    *(g_AreaCellCodes + map_offset + ((u8*)D_801F4D7C + 0x28)[row_offset]) = 0xA0;
    Actor_SelectScript(0);
    g_SpadWork->unk_01 = 1;
}
