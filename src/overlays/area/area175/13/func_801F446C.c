#include "area175_13.h"

MATCH void func_801F446C(void) {
    g_ScriptState->flag_00 |= 0x40;
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_Task->header.flags |= 0x10;
    Actor_SelectScript(0xAU);
}
