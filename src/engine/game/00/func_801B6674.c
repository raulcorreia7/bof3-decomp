#include "game_00.h"

/* Retail callers pass leftover register values the callee ignores. */
extern bool func_801B6470(s32 arg0, s32 arg1);

#ifdef NON_MATCHING
NON_MATCHING bool func_801B6674(void) {
    s32 temp;
    u8  status;
    u8* counter;

    temp   = Area_GetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y));
    status = g_GameRequestFlags;
    if (!(status & AREA_LOAD_FLAG_WORLD_MAP)) {
        return 0;
    }
    if (g_InputPressed & g_InputMasks[WORLD_INPUT_ENTER]) {
        if ((temp & BYTE_MASK) != 0xAE) {
            if ((temp & 0xF0) != 0xA0) {
                if ((g_Game.walk_flags & AREA_WALK_TRANSITION) == 0) {
                    return 0;
                }
            }
            if (!(status & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
                func_801B5BDC(g_Task->direction_08);
            }
            func_801B690C();
            g_Game.walk_flags &= ~AREA_WALK_TRANSITION;
            Game_RequestAreaChange(g_GameContextSeed, g_GameEntryPosX, g_GameEntryPosY, g_GameContextKind);
            return 1;
        }
        g_SceneEventMode = 0x37;
        ACTOR_CLEAR_STEP();
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
        if ((func_801B6470(temp, status) & BYTE_MASK) == 0) {
            return 0;
        }
        if (!(g_GameRequestFlags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            func_801B5BDC(g_Task->direction_08);
        }
        D_8014504A += 1;
        g_Game.walk_flags &= ~AREA_WALK_TRANSITION;
        D_80145048 = g_GameAreaId;
        D_80145044 = g_Task->pos.y.fixed;
        D_80145040 = g_Task->pos.x.fixed;
        Game_RequestAreaChange(g_GameContextSeed, g_GameEntryPosX, g_GameEntryPosY, g_GameContextKind);
        return 1;
    }
    if ((g_InputPressed & g_InputMasks[WORLD_INPUT_LOCATION_GUIDE]) && ((u8)(temp + 0x60) < 2)) {
        g_SceneEventMode = 0x1B;
        if (!(status & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            func_801B5BDC(g_Task->direction_08);
        }
        ACTOR_CLEAR_STEP();
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801B6674);
#endif
