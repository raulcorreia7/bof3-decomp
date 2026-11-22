#include "engine/game/00/game_00.h"

/* func_801BF5A8 */
#ifdef NON_MATCHING
NON_MATCHING void Game_BattleSetEncounterSpot(s32 x, s32 y, s32 party_slot) {
    u8     base;
    s32    off;
    s32    x_start = x;
    s32    y_start = y;
    Actor* rec;

    if (g_Game.party_size == 2) {
        base = g_PartyFormation + 1;
    } else if (g_Game.party_size == 3) {
        base = g_PartyFormation + 4;
    } else {
        base = g_PartyFormation;
    }
    if (s_CameraScrollDeltas[g_Battle.scroll_dir].dx != 0) {
        rec        = g_Task;
        off        = (((base & BYTE_MASK) * 3) + (party_slot & BYTE_MASK)) * 8;
        rec->pos.x = x_start + (FIELD(s32, D_80181CA8, off) * (s_CameraScrollDeltas[g_Battle.scroll_dir].dx / 4));
        rec->pos.y = y_start + (FIELD(s32, &D_80181CAC, off) * (s_CameraScrollDeltas[g_Battle.scroll_dir].dx / 4));
    } else {
        rec        = g_Task;
        off        = (((base & BYTE_MASK) * 3) + (party_slot & BYTE_MASK)) * 8;
        rec->pos.x = x_start - (FIELD(s32, &D_80181CAC, off) * (s_CameraScrollDeltas[g_Battle.scroll_dir].dy / 4));
        rec->pos.y = y_start + (FIELD(s32, D_80181CA8, off) * (s_CameraScrollDeltas[g_Battle.scroll_dir].dy / 4));
    }
    COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
}
#else
INCLUDE_ASM(Game_BattleSetEncounterSpot);
#endif
