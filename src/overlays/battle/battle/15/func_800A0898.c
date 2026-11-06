#include "battle_15.h"

MATCH void func_800A0898(void) {
    BattleTurn* record;

    ((volatile BattleTurn*)g_BattleTargetRecord)->hp_change = 0;
    if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) == 0) {
        func_800A3F28();
        func_801DDFEC(g_BattleTarget);
        func_801DD14C(g_BattleTarget);
        return;
    }
    /* FAKE: volatile-drop cell read keeps the constant load ahead of
     * the pointer load, so the branch delay slot takes it. */
    record               = *(BattleTurn**)&g_BattleTargetRecord;
    record->target_flags = 1;
}
