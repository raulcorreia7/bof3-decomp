#include "batl_end_00.h"

/* Ends the battle on the victory screen: applies each member's level-ups, pays out the reward zenny
 * and fills the reward and drop panels before loading the next area's archive. */
MATCH void func_801EF348(void) {
    u8 i;
    u8 j;

    if ((g_Battle.outcome.result & 0x20) != 0) {
        if (g_InputPressed == 0) {
            return;
        }
    }
    if (g_InputHeld == 0) {
        return;
    }
    for (i = 0; i < g_Battle.party_count; i++) {
        if (func_801EF928(func_801DD7AC(g_Game.members[i].chr.character_id), 0) != 0) {
            Char_GetExp(func_801DD7AC(g_Game.members[i].chr.character_id));
        }
    }
    if ((u8)func_801EF6C0() != 0) {
        g_Battle.outcome.reward_zenny += (u32)g_Battle.outcome.reward_zenny >> 1;
    }
    D_80148354 = 0;
    Menu_OpenPanelTask(1, 4);
    D_80148356 = 5;
    D_80148357 = 0;
    sprintf(g_TextVariables, D_801EEC04, g_Battle.outcome.reward_zenny);
    D_801EB4F4 = Message_GetText(6);
    if ((u32)g_Battle.outcome.reward_zenny < 30) {
        D_801463B0 = 1;
    } else {
        D_801463B0 = (u32)g_Battle.outcome.reward_zenny / 30;
    }
    if (g_Battle.outcome.drop_count != 0) {
        Menu_OpenPanelTask(0x15, 4);
        D_80148626 = 1;
        D_80148628 = 0x14;
        D_8014862A = 0x46;
        D_8014862D = ((g_Battle.outcome.drop_count - 1) / 2) * 13 + 18;
        if (g_Battle.outcome.drop_count >= 2) {
            for (i = 0; i < g_Battle.outcome.drop_count - 1; i++) {
                for (j = i + 1; j < g_Battle.outcome.drop_count; j++) {
                    if (g_Battle.outcome.drops.items[i] > g_Battle.outcome.drops.items[j]) {
                        g_Battle.outcome.drops.items[i] ^= g_Battle.outcome.drops.items[j];
                        g_Battle.outcome.drops.items[j] ^= g_Battle.outcome.drops.items[i];
                        g_Battle.outcome.drops.items[i] ^= g_Battle.outcome.drops.items[j];
                        g_Battle.outcome.drops.item_counts[i] ^= g_Battle.outcome.drops.item_counts[j];
                        g_Battle.outcome.drops.item_counts[j] ^= g_Battle.outcome.drops.item_counts[i];
                        g_Battle.outcome.drops.item_counts[i] ^= g_Battle.outcome.drops.item_counts[j];
                    }
                }
            }
        }
    }
    g_EmiStreamFlags |= 0x20;
    EMI_LoadArchive(g_GameAreaId + 0x2AB);
    {
        /* Base held once for the read-modify-write, as in retail. */
        u8* counter = (u8*)&g_Battle.ui_state;

        *counter += 1;
    }
}
