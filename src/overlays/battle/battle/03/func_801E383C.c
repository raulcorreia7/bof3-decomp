#include "battle_03.h"

MATCH void func_801E383C(void) {
    u8 value;

    if (g_Battle.selection_latch != 0) {
        value = g_BattleActorTurn->command.target;
        if ((value == TASK(PartyMember)->slot) || (value & BATTLE_TARGET_ENEMY_SIDE)) {
            TASK(PartyMember)->unk_07      = GFX_PaletteAllocFade(TASK(void), 0, 0, 0, 0);
            TASK(PartyMember)->header.step = 1;
        }
    }
}
