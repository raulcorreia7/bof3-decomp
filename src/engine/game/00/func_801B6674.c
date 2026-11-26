#include "game_00.h"
#include "menu/save_data.h"

#ifdef NON_MATCHING
NON_MATCHING bool func_801B6674(void) {
    s32 cell;
    u8  flags;
    u16 pressed;

    cell  = Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y));
    flags = g_GameRequestFlags;
    if (!(flags & AREA_LOAD_FLAG_WORLD_MAP)) {
        return 0;
    }
    pressed = g_PadStates[0].pressed;
    if (pressed & g_InputMasks[WORLD_INPUT_ENTER]) {
        if ((cell & BYTE_MASK) != 0xAE) {
            if ((cell & 0xF0) != 0xA0 && !(g_AreaWalkFlags & AREA_WALK_TRANSITION)) {
                return 0;
            }
            if (!(flags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
                Actor_RequestRoute(SELF(Actor)->direction);
            }
            func_801B690C();
            g_AreaWalkFlags &= ~AREA_WALK_TRANSITION;
            Game_RequestAreaChange(g_GameEntryAreaId, g_GameEntryPosX, g_GameEntryPosY, g_GameEntryFacing);
            return 1;
        }
        g_SceneEventState.mode = 0x37;
        ACTOR_CLEAR_STEP();
        return 1;
    }
    if (pressed & PADselect) {
        u8* counter = &D_801454F2;

        *counter += 1;
        if ((u8)*counter >= 3) {
            *counter = 0;
        }
        return 0;
    }
    if (pressed & PADstart) {
        if (!(func_801B6470(cell, flags) & BYTE_MASK)) {
            return 0;
        }
        if (!(g_GameRequestFlags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            Actor_RequestRoute(SELF(Actor)->direction);
        }
        {
            u16 area   = g_GameEntryAreaId;
            u32 x      = g_GameEntryPosX;
            u32 y      = g_GameEntryPosY;
            u8  facing = g_GameEntryFacing;

            g_SaveData.return_point.x = SELF(Actor)->pos.x.fixed;
            g_SaveData.return_point.pending += 1;
            g_AreaWalkFlags &= ~AREA_WALK_TRANSITION;
            g_SaveData.return_point.y       = SELF(Actor)->pos.y.fixed;
            g_SaveData.return_point.area_id = g_GameAreaId;
            Game_RequestAreaChange(area, x, y, facing);
        }
        return 1;
    }
    if ((pressed & g_InputMasks[WORLD_INPUT_LOCATION_GUIDE]) && (u8)(cell + 0x60) < 2) {
        g_SceneEventState.mode = 0x1B;
        if (!(flags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            Actor_RequestRoute(SELF(Actor)->direction);
        }
        ACTOR_CLEAR_STEP();
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801B6674);
#endif
