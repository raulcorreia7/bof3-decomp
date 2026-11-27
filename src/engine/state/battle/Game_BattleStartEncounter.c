#include "engine/game/00/game_00.h"

/* func_801BFE34 */
MATCH void Game_BattleStartEncounter(s32 origin_x, s32 origin_y, s32 scroll_mode) {
    s32 offset;
    s32 type;
    s32 count;
    u8  mode;
    u8  key;
    u8* record;

    mode                = D_801CD78D[(scroll_mode & BYTE_MASK) * 4];
    g_EncounterOriginX  = origin_x;
    g_EncounterOriginY  = origin_y;
    g_Battle.scroll_dir = mode;
    count               = 0;
    if (count < g_Game.party_size) {
        offset = 0;
        do {
            type        = 0;
            record      = (u8*)g_Game.members + offset;
            g_GameState = record;
            SELF_SET(record);
            key = record[0x79];
            while (1) {
                if (g_PartyBattleOrder[type & BYTE_MASK] == key)
                    break;
                type += 1;
                if ((type & BYTE_MASK) >= 3U)
                    break;
            }
            type &= BYTE_MASK;
            Game_BattleSetEncounterSpot(g_EncounterOriginX, g_EncounterOriginY, type);
            type <<= 3;
            *(s32*)((u8*)g_AreaEncounterPlacement.party + type)       = SELF(Actor)->pos.x.fixed;
            *(s32*)((u8*)&g_AreaEncounterPlacement.party[0].y + type) = SELF(Actor)->pos.y.fixed;
            SELF(Actor)->unk_48                                       = 0;
            SELF(Actor)->direction                                    = s_RouteIndexByMode[g_Battle.scroll_dir];
            Script_Request(SELF(Actor)->direction);
            offset += BATTLE_PARTY_STRIDE;
            count += 1;
        } while (count < g_Game.party_size);
    }
}
