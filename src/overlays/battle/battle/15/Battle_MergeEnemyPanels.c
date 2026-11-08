#include "battle_15.h"

/* func_8009CFEC */
MATCH void Battle_MergeEnemyPanels(void) {
    PanelOwner entries[8];
    u8         count;
    u8         i;
    u8         j;
    u8         found;

    count = 0;
    found = 0;
    for (i = 0; i < D_801EB5A8; i++) {
        for (j = 0; j < count; j++) {
            if (g_BattleEnemyBattlers[D_801ED9B0[i].owner_index].enemy_id.byte.kind !=
                g_BattleEnemyBattlers[entries[j].owner_index].enemy_id.byte.kind) {
                continue;
            }
            if (D_801ED9B0[i].panel_id != entries[j].panel_id) {
                continue;
            }
            found = 1;
            break;
        }
        if (!found) {
            entries[count] = D_801ED9B0[i];
            count++;
        }
        found = 0;
    }
    D_801EB5A8 = count;
    for (i = 0; i < D_801EB5A8; i++) {
        D_801ED9B0[i] = entries[i];
    }
}
