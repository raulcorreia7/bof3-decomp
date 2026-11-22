#include "battle_03.h"

MATCH void func_801E383C(void) {
    u8 value;

    if (g_Battle.selection_latch != 0) {
        value = g_BattleActorTurn->command.target;
        if ((value == BATTLE_WORK->slot) || (value & BATTLE_TARGET_ENEMY_SIDE)) {
            BATTLE_WORK->unk_07      = GFX_PaletteAllocFade(TASK(u8), 0, 0, 0, 0);
            BATTLE_WORK->header.step = 1;
        }
    }
}
