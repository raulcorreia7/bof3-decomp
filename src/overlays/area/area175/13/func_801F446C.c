#include "area175_13.h"

MATCH void func_801F446C(void) {
    g_ScriptState->flags |= 0x40;
    SELF(Actor)->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    SELF(Actor)->header.flags |= 0x10;
    Script_Select(0xAU);
}
