#include "area103_13.h"

MATCH void func_801F560C(void) {
    g_ScriptState->message_id = Area_FindTaggedPartySlot() + 2;
    func_801A17A0((u8*)g_ScriptState);
    g_ScriptState->flags &= 0xEF;
    if (SELF(Actor)->option_flags & ACTOR_OPT_NO_SCRIPT_START) {
        g_ScriptState->flags &= 0xDF;
    } else {
        g_ScriptState->flags |= 0x20;
    }
}
