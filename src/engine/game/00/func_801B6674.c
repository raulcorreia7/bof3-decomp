#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING bool func_801B6674(void) {
    s32 cell_code;
    u8  status;
    u8* counter;
    u16 entry_area;
    s32 entry_pos_x;
    s32 entry_pos_y;
    u8  entry_facing;

    cell_code = Area_GetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y));
    status    = g_GameRequestFlags;
    if (!(status & AREA_LOAD_FLAG_WORLD_MAP)) {
        return 0;
    }
    if (g_InputPressed & g_InputMasks[WORLD_INPUT_ENTER]) {
        if ((cell_code & BYTE_MASK) == 0xAE) {
            g_SceneEventState.mode = 0x37;
            ACTOR_CLEAR_STEP();
            return 1;
        }
        if ((cell_code & 0xF0) != 0xA0 && !(g_Game.walk_flags & AREA_WALK_TRANSITION)) {
            return 0;
        }
        if (!(status & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            Actor_RequestRoute(g_Task->direction);
        }
        func_801B690C();
        entry_area   = g_GameEntryAreaId;
        entry_pos_x  = g_GameEntryPosX;
        entry_pos_y  = g_GameEntryPosY;
        entry_facing = g_GameEntryFacing;
        g_Game.walk_flags &= ~AREA_WALK_TRANSITION;
        Game_RequestAreaChange(entry_area, entry_pos_x, entry_pos_y, entry_facing);
        return 1;
    }
    if (g_InputPressed & PADselect) {
        counter = &D_801454F2;
        *counter += 1;
        if ((u8)*counter < 3) {
            return 0;
        }
        *counter = 0;
        return 0;
    }
    if (g_InputPressed & PADstart) {
        if ((func_801B6470(cell_code, status) & BYTE_MASK) == 0) {
            return 0;
        }
        if (!(g_GameRequestFlags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            Actor_RequestRoute(g_Task->direction);
        }
        entry_area   = g_GameEntryAreaId;
        entry_pos_x  = g_GameEntryPosX;
        entry_pos_y  = g_GameEntryPosY;
        entry_facing = g_GameEntryFacing;
        D_8014504A += 1;
        g_Game.walk_flags &= ~AREA_WALK_TRANSITION;
        D_80145044 = g_Task->pos.y.fixed;
        D_80145040 = g_Task->pos.x.fixed;
        D_80145048 = g_GameAreaId;
        Game_RequestAreaChange(entry_area, entry_pos_x, entry_pos_y, entry_facing);
        return 1;
    }
    if ((g_InputPressed & g_InputMasks[WORLD_INPUT_LOCATION_GUIDE]) && ((u8)(cell_code + 0x60) < 2)) {
        g_SceneEventState.mode = 0x1B;
        if (!(status & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            Actor_RequestRoute(g_Task->direction);
        }
        ACTOR_CLEAR_STEP();
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801B6674);
#endif
