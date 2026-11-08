#include "battle_03.h"

/* rolls the current enemy's two drop rows: a row with an item and rate passes when its g_BattleDropChances chance is
 * at least RANDOM_MASK(0xFF); a passing item bumps its drop count or is appended with count 1 (at most 15 entries),
 * and the row's item is cleared.
 */
/* func_801E531C */
MATCH void Battle_RollEnemyDrops(void) {
    DropChances chances;
    u8          i;
    u8          j;

    chances = g_BattleDropChances;
    for (i = 0; i < 2; i++) {
        if (g_BattleCurrentEnemy->drops[i].item != 0 && g_BattleCurrentEnemy->drops[i].rate != 0) {
            if (chances.chance[g_BattleCurrentEnemy->drops[i].rate] >= (RANDOM_MASK(BYTE_MASK))) {
                for (j = 0; j < g_BattleOutcome.drop_count; j++) {
                    if (g_BattleOutcome.drops.items[j] == g_BattleCurrentEnemy->drops[i].item) {
                        g_BattleOutcome.drops.item_counts[j]++;
                        g_BattleCurrentEnemy->drops[i].item = 0;
                        goto next; /* the item is already listed */
                    }
                }
                g_BattleOutcome.drops.items[g_BattleOutcome.drop_count]       = g_BattleCurrentEnemy->drops[i].item;
                g_BattleOutcome.drops.item_counts[g_BattleOutcome.drop_count] = 1;
                if (g_BattleOutcome.drop_count < BATTLE_DROP_COUNT_MAX) {
                    g_BattleOutcome.drop_count++;
                }
                g_BattleCurrentEnemy->drops[i].item = 0;
            }
        }
    next:;
    }
}
