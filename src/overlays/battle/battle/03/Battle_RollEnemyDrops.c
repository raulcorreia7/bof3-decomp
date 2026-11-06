#include "battle_03.h"

/* rolls the current enemy's two drop rows: a row with an item and rate passes when its g_BattleDropChances chance is
 * at least RANDOM_MASK(0xFF); a passing item bumps its spoils count or is appended with count 1 (at most 15 entries),
 * and the row's item is cleared.
 */
/* func_801E531C */
MATCH void Battle_RollEnemyDrops(void) {
    DropChances chances;
    u8          i;
    u8          j;

    chances = g_BattleDropChances;
    for (i = 0; i < 2; i++) {
        if (g_BattleCurrentEnemy->drops[i].item_00 != 0 && g_BattleCurrentEnemy->drops[i].rate_02 != 0) {
            if (chances.chance[g_BattleCurrentEnemy->drops[i].rate_02] >= (rand() & BYTE_MASK)) {
                for (j = 0; j < D_80146326.count; j++) {
                    if (D_80146326.items[j] == g_BattleCurrentEnemy->drops[i].item_00) {
                        D_80146326.counts[j]++;
                        g_BattleCurrentEnemy->drops[i].item_00 = 0;
                        goto next; /* the item is already listed */
                    }
                }
                D_80146326.items[D_80146326.count]  = g_BattleCurrentEnemy->drops[i].item_00;
                D_80146326.counts[D_80146326.count] = 1;
                if (D_80146326.count < BATTLE_SPOILS_COUNT_MAX) {
                    D_80146326.count++;
                }
                g_BattleCurrentEnemy->drops[i].item_00 = 0;
            }
        }
    next:;
    }
}
