#include "boss054_16.h"

MATCH void func_800C1D7C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_800C182C;
    handlers.handlers[((PartyBattler*)g_Task)->step]();
    if (ACTOR_IN_USE(*(PartyBattler*)g_Task)) {
        func_8014D978();
        func_8014D290();
    }
}
