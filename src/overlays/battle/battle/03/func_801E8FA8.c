#include "battle_03.h"

MATCH u8 func_801E8FA8(void) {
    u8* field;
    u8  start_index;
    u16 mask;
    u8  index;

    field = &D_801EB4E0->slot;
    if (*field < 3) {
        mask = g_BattlePartyBattlers[*field].stats.status;
    } else {
        mask = ENEMY_COMBATANT(*field).status_82;
    }

    start_index = g_SpadWork->word_08.byte.unk_0B;
    mask &= 0x58u;
    index = (start_index + 1u) & 0xFu;
    while (index != start_index) {
        if ((((s32)mask >> index) & 1) != 0) {
            return index;
        }
        index = (index + 1u) & 0xFu;
    }

    return g_SpadWork->word_08.byte.unk_0B;
}
