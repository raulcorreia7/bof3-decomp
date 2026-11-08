#include "battle_15.h"

MATCH void func_8009F9E0(void) {
    BattleTurn* ptr;

    g_Battle.target_record->target_flags |= BATTLE_HIT_AP;
    ((s16*)(g_Battle.target_record))[2] = -5;
    ptr                                 = g_Battle.target_record;
    ptr->ap_change                      = -1;
}
