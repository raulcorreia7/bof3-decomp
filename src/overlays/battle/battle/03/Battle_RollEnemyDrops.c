#include "battle_03.h"

/* rolls the current enemy's two drop rows. */
/* func_801E531C */
MATCH void Battle_RollEnemyDrops(void) {
    DropChances chances;
    u8          i;
    u8          j;

    chances = g_BattleDropChances;
    for (i = 0; i < 2; i++) {
        if (g_BattleCurrentEnemy->drops[i].item != 0 && g_BattleCurrentEnemy->drops[i].rate != 0) {
            if (chances.chance[g_BattleCurrentEnemy->drops[i].rate] >= (RANDOM_MASK(BYTE_MASK))) {
                for (j = 0; j < g_Battle.outcome.drop_count; j++) {
                    if (g_Battle.outcome.drops.items[j] == g_BattleCurrentEnemy->drops[i].item) {
                        g_Battle.outcome.drops.item_counts[j]++;
                        g_BattleCurrentEnemy->drops[i].item = 0;
                        goto next; /* the item is already listed */
                    }
                }
                g_Battle.outcome.drops.items[g_Battle.outcome.drop_count]       = g_BattleCurrentEnemy->drops[i].item;
                g_Battle.outcome.drops.item_counts[g_Battle.outcome.drop_count] = 1;
                if (g_Battle.outcome.drop_count < BATTLE_DROP_COUNT_MAX) {
                    g_Battle.outcome.drop_count++;
                }
                g_BattleCurrentEnemy->drops[i].item = 0;
            }
        }
    next:;
    }
}
