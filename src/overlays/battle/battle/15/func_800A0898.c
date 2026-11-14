#include "battle_15.h"

MATCH void func_800A0898(void) {
    BattleTurn* record;

    ((volatile BattleTurn*)g_Battle.target_record)->hp_change = 0;
    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
        Battle_MarkDamageApplied();
        func_801DDFEC(g_Battle.target);
        func_801DD14C(g_Battle.target);
        return;
    }
    /* FAKE: volatile-drop cell read keeps the constant load ahead of
     * the pointer load, so the branch delay slot takes it. */
    record               = *(BattleTurn**)&g_Battle.target_record;
    record->target_flags = 1;
}
