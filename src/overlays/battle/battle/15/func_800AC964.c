#include "battle_15.h"

/* One row of the enemy panel list: an enemy id and the live slots still to place. */
typedef struct BattleEnemyGroup {
    s16 id;
    u16 count;
} BattleEnemyGroup;

#ifdef NON_MATCHING
/* Groups the live enemy slots by enemy id, puts the largest group first, then opens one panel per
 * placed enemy down the column the battle's scroll direction selects. */
/* func_800AC964 */
NON_MATCHING void func_800AC964(void) {
    BattleEnemyGroup groups[8];
    BattleEnemyGroup swap;
    u8               i;
    u8               j;
    u8               k;
    u8               total;
    u8               found;
    u8               panels;
    s32              panel;
    s32              x;
    s32              y;
    s32              saved_y;

    total = 0;
    for (i = 0; i < 8; i++) {
        groups[i].id = -1;
    }
    for (i = 0; i < g_Battle.enemy_count; i++) {
        if (g_BattleEnemyBattlers[i].header.flags & 1) {
            found = 0;
            for (j = 0; j < total; j++) {
                if (groups[j].id == g_BattleEnemyBattlers[i].enemy_id.byte.type) {
                    found           = 1;
                    groups[j].count = groups[j].count + 1;
                    break;
                }
            }
            if (!found) {
                groups[total].count = 1;
                groups[total].id    = g_BattleEnemyBattlers[i].enemy_id.byte.type;
                total               = total + 1;
            }
        }
    }
    if (g_Battle.enemy_count >= 2) {
        for (j = 1; j < total; j++) {
            for (i = j - 1; i < total - 1; i++) {
                if ((s16)groups[i].count < (s16)groups[i + 1].count) {
                    swap          = groups[i];
                    groups[i]     = groups[i + 1];
                    groups[i + 1] = swap;
                }
            }
        }
    }
    x      = D_800B51E8[g_Battle.scroll_dir][0];
    y      = D_800B51E8[g_Battle.scroll_dir][1];
    panels = 0;
    /* The enemy panels fill the ks below 0xC, one per enemy the side shows. */
    if (g_Battle.scroll_dir >= 2) {
        for (i = 0; groups[i].id != -1; i++) {
            k       = 0;
            j       = groups[i].count;
            y       = y - 0x15;
            y       = y - ((j - 1) << 3);
            saved_y = y;
            for (; k < g_Battle.enemy_count; k++) {
                if (j == 0) {
                    break;
                }
                if (groups[i].id == g_BattleEnemyBattlers[k].enemy_id.byte.type) {
                    groups[i].count = groups[i].count - 1;
                    j               = j - 1;
                    UI_PanelOpenTask(0xC - panels, 3);
                    panel                               = 0xC - panels++;
                    g_UiPanelTasks[panel].mode          = 4;
                    g_UiPanelTasks[panel].state         = 0;
                    g_UiPanelTasks[panel].u.addr.unk_10 = x;
                    g_UiPanelTasks[panel].pos.vx        = x;
                    g_UiPanelTasks[panel].u.addr.unk_12 = y;
                    g_UiPanelTasks[panel].pos.vy        = y;
                    y                                   = y + 8;
                    g_UiPanelTasks[panel].unk_0A        = k + 3;
                    g_UiPanelTasks[panel].unk_08        = 0;
                    g_UiPanelTasks[panel].unk_09        = 0;
                }
            }
            y = saved_y - 2;
        }
    } else {
        i = 0;
        while (1) {
            y = (y + 0x15) + (((s16)groups[i].count - 1) << 3);
            i++;
            /* The last group ends the list. */
            if (groups[i].id == -1) {
                break;
            }
            y = y + 2;
        }
        for (i = 0; groups[i].id != -1; i++) {
            k       = 0;
            j       = groups[i].count;
            y       = y - 0x15;
            y       = y - ((j - 1) << 3);
            saved_y = y;
            for (; k < g_Battle.enemy_count; k++) {
                if (j == 0) {
                    break;
                }
                if (groups[i].id == g_BattleEnemyBattlers[k].enemy_id.byte.type) {
                    groups[i].count = groups[i].count - 1;
                    j               = j - 1;
                    UI_PanelOpenTask(0xC - panels, 3);
                    panel                               = 0xC - panels++;
                    g_UiPanelTasks[panel].mode          = 4;
                    g_UiPanelTasks[panel].state         = 0;
                    g_UiPanelTasks[panel].u.addr.unk_10 = x;
                    g_UiPanelTasks[panel].pos.vx        = x;
                    g_UiPanelTasks[panel].u.addr.unk_12 = y;
                    g_UiPanelTasks[panel].pos.vy        = y;
                    y                                   = y + 8;
                    g_UiPanelTasks[panel].unk_0A        = k + 3;
                    g_UiPanelTasks[panel].unk_08        = 0;
                    g_UiPanelTasks[panel].unk_09        = 0;
                }
            }
            y = saved_y - 2;
        }
    }
}
#else
INCLUDE_ASM(func_800AC964);
#endif
