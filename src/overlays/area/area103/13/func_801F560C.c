#include "area103_13.h"

MATCH void func_801F560C(void) {
    g_ScriptState->unk_08 = Area_FindTaggedPartySlot() + 2;
    func_801A17A0((u8*)g_ScriptState);
    g_ScriptState->flag_00 &= 0xEF;
    if (g_Task->option_flags & ACTOR_OPT_NO_SCRIPT_START) {
        g_ScriptState->flag_00 &= 0xDF;
    } else {
        g_ScriptState->flag_00 |= 0x20;
    }
}
