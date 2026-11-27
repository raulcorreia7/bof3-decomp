#include "engine/game/00/game_00.h"

/* func_801BF448 */
MATCH void Game_BattlePlaceMembers(void) {
    s32    tab;
    s32    count;
    s32    rec_off;
    s32    i;
    s16    val;
    u8     key;
    u8*    rec;
    Actor* work;

    count = 0;
    if (count < g_Game.party_size) {
        tab     = 0;
        rec_off = 0;
        do {
            i           = 0;
            rec         = (u8*)g_Game.members + rec_off;
            g_GameState = rec;
            SELF_SET(rec);
            key = rec[0x79];
            while (1) {
                if (g_PartyFieldOrder[i & BYTE_MASK] == key)
                    break;
                i += 1;
                if ((i & BYTE_MASK) >= 3U)
                    break;
            }
            SELF(Actor)->pos.x.fixed = *(s32*)((u8*)g_AreaEncounterPlacement.party + tab);
            val                      = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed = *(s32*)((u8*)&g_AreaEncounterPlacement.party[0].y + tab));
            work                     = SELF(Actor);
            work->param.unk_0B       = 0;
            COORD_INT(work->pos.z)   = val;
            if ((g_Characters[g_GameState->character_index].status & STATUS_KO) != 0)
                Script_Select((g_Battle.scroll_dir + 0x1C));
            else
                Script_Select(g_Battle.scroll_dir);
            tab += 8;
            rec_off += BATTLE_PARTY_STRIDE;
        } while (++count < g_Game.party_size);
    }
}
