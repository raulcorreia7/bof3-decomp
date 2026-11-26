#include "battle_03.h"

MATCH void func_801DF768(void) {
    if ((g_Battle.selection_latch != 0u) && ((g_BattleActorTurn->command.target == TASK(PartyMember)->slot) || ((g_BattleActorTurn->command.target & BATTLE_TARGET_PARTY_SIDE) != 0u))) {
        TASK(PartyMember)->unk_07      = GFX_PaletteAllocFade(TASK(void), 0, 0, 0, 0);
        TASK(PartyMember)->header.step = 1u;
    }
}
