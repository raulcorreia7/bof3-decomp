#include "battle_03.h"

MATCH u8 func_801E8FA8(void) {
    u8* field;
    u8  start_index;
    u16 mask;
    u8  index;

    field = &g_BattleEffectBattler->slot;
    if (*field < 3) {
        mask = g_Game.members[*field].chr.status;
    } else {
        mask = ENEMY_COMBATANT(*field).status;
    }

    start_index = g_Task->param.unk_0B;
    mask &= 0x58u;
    index = (start_index + 1u) & 0xFu;
    while (index != start_index) {
        if (((mask >> index) & 0x1) != 0) {
            return index;
        }
        index = (index + 1u) & 0xFu;
    }

    return g_Task->param.unk_0B;
}
