#include "battle_03.h"

MATCH u8 func_801DA69C(u32 enemy_index) {
    s8 owner_index;
    s8 scan_index;
    u8 slot_kind;

    enemy_index &= 0xFF;
    slot_kind   = g_BattleEnemyBattlers[enemy_index].enemy_id.byte.kind;
    owner_index = 7;
    while (owner_index >= 0) {
        if (D_8014833A[owner_index + 5].kind_00 == enemy_index + 3u) {
            break;
        }
        owner_index -= 1;
    }

    for (scan_index = 7; scan_index > owner_index; scan_index--) {
        u8 ui_mode;
        u8 ui_kind;

        ui_mode = D_80148333[((scan_index + 5) * 9) << 2];
        if (ui_mode == 2u) {
            continue;
        }
        if (ui_mode == 3u) {
            continue;
        }
        ui_kind = D_8014833A[scan_index + 5].kind_00;
        if (ENEMY_COMBATANT(ui_kind).enemy_id.byte.kind == slot_kind) {
            return false;
        }
    }

    return true;
}
