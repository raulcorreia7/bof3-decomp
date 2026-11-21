#include "engine/game/00/game_00.h"

#define SCRATCH ((s32*)&g_ScratchPad)

/* func_801BFB34 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_PlaceFieldMembers(void) {
    PartyMember* member;
    s32          i;
    s32          j;
    s32          size;
    s32          count;
    s32          value;
    u8*          party_size;
    /* FAKE: unused frame, 32 bytes. */
    FAKE_STACK_PADS(u8, 32);

    i = 0;
    if ((s32)g_Game.party_size > 0) {
        count = g_Game.party_size;
        do {
            SCRATCH[i] = g_Game.members[i].pos.x.fixed;
            i++;
        } while (i < count);
    }
    size = g_Game.party_size;
    i    = 0;
    if (size != 0) {
        do {
            for (j = 0; j < (u8)size; j++) {
                if (g_PartyBattleOrder[j] == g_Game.members[i].chr.character_id)
                    break;
            }
            g_Game.members[i].pos.x.fixed = SCRATCH[j];
            i++;
            size = g_Game.party_size;
        } while (i < size);
    }
    i = 0;
    if ((s32)g_Game.party_size > 0) {
        count = g_Game.party_size;
        do {
            SCRATCH[i] = g_Game.members[i].pos.y.fixed;
            i++;
        } while (i < count);
    }
    size = g_Game.party_size;
    i    = 0;
    if (size != 0) {
        do {
            for (j = 0; j < (u8)size; j++) {
                if (g_PartyBattleOrder[j] == g_Game.members[i].chr.character_id)
                    break;
            }
            value                                = SCRATCH[j];
            g_Game.members[i].pos.y.fixed        = value;
            g_Game.members[i].pos.z.part.integer = Area_ReadHeight(g_Game.members[i].pos.x.fixed, value);
            i++;
            party_size = &g_Game.party_size;
            size       = *party_size;
        } while (i < size);
    }
    if (!(g_Battle.outcome.options & 0x80)) {
        for (i = 0; i < g_Game.party_size; i++) {
            member         = &g_Game.members[i];
            g_Game.current = member;
            TASK_SET(member);
            g_Task->direction              = s_RouteIndexByMode[g_Battle.scroll_dir];
            ((PartyMember*)g_Task)->unk_29 = 6;
            if (i != 0) {
                ((PartyMember*)g_Task)->unk_07 = 0;
                ((PartyMember*)g_Task)->pad_06 = ((PartyMember*)g_Task)->slot - 1;
            }
            func_801C3204();
            Script_Select(g_Task->direction);
        }
    } else {
        Scene_SetupParty(g_Game.battle_order);
        Party_RunFrame();
    }
}
#else
INCLUDE_ASM(Battle_PlaceFieldMembers);
#endif
