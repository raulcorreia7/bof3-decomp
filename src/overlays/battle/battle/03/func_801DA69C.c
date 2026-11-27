#include "battle_03.h"

MATCH u8 func_801DA69C(u32 enemy_index) {
    s8 owner_index;
    s8 scan_index;
    u8 slot_type;

    enemy_index &= BYTE_MASK;
    slot_type   = g_BattleEnemyBattlers[enemy_index].enemy_id.byte.type;
    owner_index = 7;
    while (owner_index >= 0) {
        if (D_8014833A[owner_index + 5].type == enemy_index + 3u) {
            break;
        }
        owner_index -= 1;
    }

    for (scan_index = 7; scan_index > owner_index; scan_index--) {
        u8 ui_mode;
        u8 ui_type;

        ui_mode = g_UIPanelTasks[scan_index + 5].state;
        if (ui_mode == 2u) {
            continue;
        }
        if (ui_mode == 3u) {
            continue;
        }
        ui_type = D_8014833A[scan_index + 5].type;
        if (ENEMY_COMBATANT(ui_type).enemy_id.byte.type == slot_type) {
            return false;
        }
    }

    return true;
}
