#include "area152_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F44D0(void) {
    s32 row_offset;
    s32 map_offset;

    if (g_Characters[CHAR_SLOT_RYU].character_id == CHAR_ID_RYU_PAJAMAS || (D_80146871 & 1)) {
        Actor_Clear();
        return;
    }
    Game_FindAreaHandler();
    Area_FindSceneRecord(0x205);

    g_SpadWork->unk_48            = 0;
    g_SpadWork->flags_24          = 0;
    g_SpadWork->unk_2A            = 0;
    g_SpadWork->tint.bytes.unk_5D = 0;
    g_SpadWork->tint.bytes.unk_5E = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;

    row_offset = g_SpadWork->unk_0B * 4;
    map_offset = *((u8*)D_801F4C3C + 0xD + row_offset) * MEM(u8, 0x80104000);
    *(g_AreaCellCodes + map_offset + *((u8*)D_801F4C3C + 0xC + row_offset)) = 0xA0;
    Actor_SelectScript(0);
    ((u8*)g_SpadWork)[1] = 1;
}
