#include "engine/game/00/game_00.h"

#define SCRATCH ((s32*)&g_ScratchPad)

/* func_801BFB34 */
MATCH void Game_BattlePlaceFieldMembers(void) {
    PartyMember* member;
    s32          i;
    s32          j;
    u8           size;
    u8           count;
    s32          value;
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u8, 16);

    i = 0;
    while (i < g_PartySize) {
        SCRATCH[i] = g_Game.members[i].pos.x.fixed;
        i++;
    }
    size = g_PartySize;
    i    = 0;
    if (size != 0) {
        do {
            count = size;
            for (j = 0; j < count; j++) {
                if (g_PartyBattleOrder[j] == g_Game.members[i].chr.character_id)
                    break;
            }
            g_Game.members[i].pos.x.fixed = SCRATCH[j];
            i++;
            size = g_PartySize;
        } while (i < size);
    }
    i = 0;
    while (i < g_PartySize) {
        SCRATCH[i] = g_Game.members[i].pos.y.fixed;
        i++;
    }
    size = g_PartySize;
    i    = 0;
    if (size != 0) {
        do {
            count = size;
            for (j = 0; j < count; j++) {
                if (g_PartyBattleOrder[j] == g_Game.members[i].chr.character_id)
                    break;
            }
            value                                = SCRATCH[j];
            g_Game.members[i].pos.y.fixed        = value;
            g_Game.members[i].pos.z.part.integer = Area_HeightRead(g_Game.members[i].pos.x.fixed, value);
            i++;
            size = g_PartySize;
        } while (i < size);
    }
    if (!(g_Battle.outcome.options & 0x80)) {
        for (i = 0; i < g_PartySize; i++) {
            member      = &g_Game.members[i];
            g_GameState = member;
            TASK_SET(member);
            TASK(Actor)->direction    = s_RouteIndexByMode[g_Battle.scroll_dir];
            TASK(PartyMember)->unk_29 = 6;
            if (i != 0) {
                TASK(PartyMember)->unk_07 = 0;
                TASK(PartyMember)->pad_06 = TASK(PartyMember)->slot - 1;
            }
            func_801C3204();
            Script_Select(TASK(Actor)->direction);
        }
    } else {
        Scene_SetupParty(g_Game.battle_order);
        Party_RunFrame();
    }
}
