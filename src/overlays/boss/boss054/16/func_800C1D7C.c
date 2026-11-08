#include "boss054_16.h"

MATCH void func_800C1D7C(void) {
    BossEffect054Steps handlers;

    handlers = D_800C182C;
    handlers.steps[((PartyBattler*)g_Task)->header.step]();
    if (ACTOR_IN_USE(*(PartyBattler*)g_Task)) {
        func_8014D978();
        func_8014D290();
    }
}
