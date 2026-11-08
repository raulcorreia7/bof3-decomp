#include "battle_15.h"

MATCH void func_800A8450(void) {
    volatile u8* selection_index;
    u8           value;

    selection_index                              = &g_BattleActiveBattler;
    g_Game.members[*selection_index].header.mode = 6u;
    value                                        = 4u;
    g_Game.members[*selection_index].header.step = value;
    g_Game.members[*selection_index].unk_03      = value;
    g_Game.members[*selection_index].unk_04      = 0u;
    BATTLE_WORK->header.mode++;
}
