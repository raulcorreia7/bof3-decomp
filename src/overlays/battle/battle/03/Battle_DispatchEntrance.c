#include "battle_03.h"

/* Copies the four entrance sub-step words at 0x801D0C1C to the stack and dispatches the entry the sub-step byte 0x801462E2 selects. */
/* func_801D17C4 */
MATCH void Battle_DispatchEntrance(void) {
    BattleEntrances handlers;

    handlers = g_BattleEntrances;
    handlers.handlers[g_Battle.phase.sub_step]();
}
