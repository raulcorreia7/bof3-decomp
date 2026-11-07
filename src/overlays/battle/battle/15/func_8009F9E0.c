#include "battle_15.h"

MATCH void func_8009F9E0(void) {
    BattleTurn* ptr;

    g_BattleTargetRecord->target_flags |= BATTLE_HIT_AP;
    ((s16*)(g_BattleTargetRecord))[2] = -5;
    ptr                               = g_BattleTargetRecord;
    ptr->ap_change                    = -1;
}
