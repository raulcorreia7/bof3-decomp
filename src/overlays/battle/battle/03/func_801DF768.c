#include "battle_03.h"

MATCH void func_801DF768(void) {
    if ((g_Battle.selection_latch != 0u) && ((g_BattleActorTurn->command.target == SELF(PartyMember)->slot) || ((g_BattleActorTurn->command.target & BATTLE_TARGET_PARTY_SIDE) != 0u))) {
        SELF(PartyMember)->unk_07      = GFX_PaletteAllocFade(SELF(void), 0, 0, 0, 0);
        SELF(PartyMember)->header.step = 1u;
    }
}
