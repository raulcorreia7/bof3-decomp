#include "battle_03.h"

MATCH void func_801DF768(void) {
    if ((g_Battle.selection_latch != 0u) && ((g_BattleActorTurn->command.target == BATTLE_WORK->slot) || ((g_BattleActorTurn->command.target & BATTLE_TARGET_PARTY_SIDE) != 0u))) {
        BATTLE_WORK->unk_07      = GFX_PaletteAllocFade(TASK(u8), 0, 0, 0, 0);
        BATTLE_WORK->header.step = 1u;
    }
}
