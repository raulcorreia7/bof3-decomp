#include "area067_14.h"

MATCH void func_801F318C(void) {
    u16* channel = (u16*)&g_UIWindowChannel;
    u16  bits    = *channel;

    g_ScriptVars[0] = 0x32;
    *channel        = bits | 0x2;
    Actor_Clear();
}
