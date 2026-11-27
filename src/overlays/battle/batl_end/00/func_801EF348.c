#include "batl_end_00.h"

/* Ends the battle on the victory screen: applies each member's level-ups, pays out the reward zenny
 * and fills the reward and drop panels before loading the next area's archive. */
MATCH void func_801EF348(void) {
    u8 i;
    u8 j;

    if ((g_Battle.outcome.result & 0x20) != 0) {
        if (g_PadStates[0].pressed == 0) {
            return;
        }
    }
    if (g_PadStates[0].held == 0) {
        return;
    }
    for (i = 0; i < g_Battle.party_count; i++) {
        if (func_801EF928(func_801DD7AC(g_Game.members[i].chr.character_id), 0) != 0) {
            Char_ApplyLevelUps(func_801DD7AC(g_Game.members[i].chr.character_id));
        }
    }
    if ((u8)func_801EF6C0() != 0) {
        g_Battle.outcome.reward_zenny += (u32)g_Battle.outcome.reward_zenny >> 1;
    }
    g_UIPanelTasks[1].active = 0;
    UI_PanelOpenTask(1, 4);
    g_UIPanelTasks[1].mode  = 5;
    g_UIPanelTasks[1].state = 0;
    sprintf(g_TextVariables, D_801EEC04, g_Battle.outcome.reward_zenny);
    g_BattleEventSlots[0].payload = UI_MessageGetText(6);
    if ((u32)g_Battle.outcome.reward_zenny < 30) {
        D_801463B0 = 1;
    } else {
        D_801463B0 = (u32)g_Battle.outcome.reward_zenny / 30;
    }
    if (g_Battle.outcome.drop_count != 0) {
        UI_PanelOpenTask(0x15, 4);
        g_UIPanelTasks[21].mode   = 1;
        D_80148628                = 0x14;
        D_8014862A                = 0x46;
        g_UIPanelTasks[21].unk_09 = ((g_Battle.outcome.drop_count - 1) / 2) * 13 + 18;
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
    EMI_ArchiveLoad(g_GameAreaId + EMI_SLOT_AREA);
    {
        /* Base held once for the read-modify-write, as in retail. */
        u8* counter = (u8*)&g_Battle.ui_mode;

        *counter += 1;
    }
}
