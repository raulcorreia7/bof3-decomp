#include "area135_14.h"

MATCH void func_801F41C8(void) {
    s32 index;
    u8  entry_x;
    u8  entry_y;
    u8* flags;

    index = g_ScriptState->script_index - 6;
    if (g_GameCellType == 4) {
        entry_x = D_801F6AAC[(u8)index * 2];
        entry_y = D_801F6AAD[(u8)index * 2];
        Game_RequestAreaChange(AREA_ID_BLACK_SHIP_EARLY, TO_COORD(entry_x), TO_COORD(entry_y), AREA_ENTRY_MAP_LOADING | FACING_UP);
    } else {
        entry_x = D_801F6AB4[(u8)index * 2];
        entry_y = D_801F6AB5[(u8)index * 2];
        Game_RequestAreaChange(AREA_ID_BLACK_SHIP_EARLY, TO_COORD(entry_x), TO_COORD(entry_y), AREA_ENTRY_MAP_LOADING | FACING_UP);
    }
    flags = &D_80143FBC;
    *flags |= 8;
}
