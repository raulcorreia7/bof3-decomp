#include "engine/game/00/game_00.h"

#define SCRATCH ((s32*)&g_ScratchPad)

/* func_801BFB34 */
#ifdef NON_MATCHING
NON_MATCHING void Game_BattlePlaceFieldMembers(void) {
    PartyMember* member;
    s32          i;
    s32          j;
    s32          size;
    s32          count;
    s32          value;
    /* FAKE: unused frame, 32 bytes. */
    FAKE_STACK_PADS(u8, 32);

    i = 0;
    if ((s32)g_PartySize > 0) {
        count = g_PartySize;
        do {
            SCRATCH[i] = g_Game.members[i].pos.x.fixed;
            i++;
        } while (i < count);
    }
    size = g_PartySize;
    i    = 0;
    if (g_PartySize != 0) {
        do {
            for (j = 0; j < (u8)size; j++) {
                if (g_PartyBattleOrder[j] == g_Game.members[i].chr.character_id)
                    break;
            }
            g_Game.members[i].pos.x.fixed = SCRATCH[j];
            i++;
            size = g_PartySize;
        } while (i < size);
    }
    i = 0;
    if ((s32)g_PartySize > 0) {
        count = g_PartySize;
        do {
            SCRATCH[i] = g_Game.members[i].pos.y.fixed;
            i++;
        } while (i < count);
    }
    size = g_PartySize;
    i    = 0;
    if (size != 0) {
        do {
            for (j = 0; j < (u8)size; j++) {
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
#else
INCLUDE_ASM(Game_BattlePlaceFieldMembers);
#endif
