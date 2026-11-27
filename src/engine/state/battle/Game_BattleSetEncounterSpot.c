#include "engine/game/00/game_00.h"

/* func_801BF5A8 */
/* Places the current actor at its party slot of the formation, turned to the camera scroll. */
MATCH void Game_BattleSetEncounterSpot(s32 x, s32 y, s32 party_slot) {
    u8 base;

    if (g_PartySize == 2) {
        base = g_PartyFormation + 1;
    } else if (g_PartySize == 3) {
        base = g_PartyFormation + 4;
    } else {
        base = g_PartyFormation;
    }
    if (s_CameraScrollDeltas[g_Battle.scroll_dir].dx != 0) {
        Actor* actor = SELF(Actor);
        s32    slot  = party_slot & BYTE_MASK;
        s32    row   = (base * 3) + slot;

        actor->pos.x.fixed = x + D_80181CA8[row][0] * (s_CameraScrollDeltas[g_Battle.scroll_dir].dx / 4);
        actor->pos.y.fixed = y + D_80181CA8[row][1] * (s_CameraScrollDeltas[g_Battle.scroll_dir].dx / 4);
    } else {
        s32    slot  = party_slot & BYTE_MASK;
        s32    row   = (base * 3) + slot;
        Actor* actor = SELF(Actor);

        actor->pos.x.fixed = x - D_80181CA8[row][1] * (s_CameraScrollDeltas[g_Battle.scroll_dir].dy / 4);
        actor->pos.y.fixed = y + D_80181CA8[row][0] * (s_CameraScrollDeltas[g_Battle.scroll_dir].dy / 4);
    }
    COORD_INT(SELF(Actor)->pos.z) = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
}
