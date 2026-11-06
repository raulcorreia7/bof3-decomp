#include "game_00.h"

/* The retail code never reads $a0 or $a1; the callers' arguments are leftover register values kept in the prototypes. */
MATCH s32 func_801B6470(void) {
    u16 world_id;
    s32 index;
    s32 i;
    s32 map_id;
    s32 x;
    s32 y;

    if ((g_GameFlags & 0x4000) == 0 && (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) != 0xC) {
        if (LOHU(g_GameAreaId) != 0xBD) {
            if ((func_801B6610(D_80145EC6, D_80145ECA) & 0xFF) != 0) {
                return 0;
            }
            if ((g_AreaWalkFlags & AREA_WALK_TRANSITION) != 0) {
                return 0;
            }
            world_id = MEM(u16, GAME_AREA_ID_ADDR);
            for (i = 0; i < 10; i++) {
                if (world_id == D_801CD24C[i].area_id) {
                    g_GameContextKind = 4;
                    g_GameContextSeed = D_801CD24C[i].map_id;
                    g_GameEntryPosX   = D_801CD24C[i].x << 16;
                    g_GameEntryPosY   = D_801CD24C[i].y << 16;
                    return 1;
                }
            }
            return 0;
        }
        index             = D_8014933C == 0 ? 3 : 0;
        map_id            = s_AreaScenePositions[index];
        g_GameContextSeed = map_id;
        x                 = s_AreaScenePositions[index + 1];
        g_GameEntryPosX   = x << 16;
        y                 = s_AreaScenePositions[index + 2];
        g_GameContextKind = 4;
        g_GameEntryPosY   = y << 16;
        return 1;
    }
    return 0;
}
