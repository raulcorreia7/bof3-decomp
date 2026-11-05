#include "battle_15.h"

MATCH void func_800A0898(void) {
    u8* record;

    g_BattleTargetRecord[2] = 0;
    if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) == 0) {
        func_800A3F28();
        func_801DDFEC(g_BattleTarget);
        func_801DD14C(g_BattleTarget);
        return;
    }
    /* FAKE: volatile-drop cell read keeps the constant load ahead of
     * the pointer load, so the branch delay slot takes it. */
    record             = *(u8**)&g_BattleTargetRecord;
    ((u8*)(record))[8] = 1;
}
