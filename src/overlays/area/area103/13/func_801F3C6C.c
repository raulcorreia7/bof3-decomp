#include "area103_13.h"

MATCH void func_801F3C6C(void) {
    s32 slot;
    s32 beat;

    if (*g_ScriptVars == 0xC) {
        g_Task->header.step++;
        g_AreaSceneMode                 = 0x23;
        slot                            = Actor_FindFreeSlot() & 0xFF;
        g_ActorSlots[slot].header.flags = 1;
        g_ActorSlots[slot].type         = 0x18;
        g_ActorSlots[slot].header.mode  = 0x17;
        g_ActorSlots[slot].header.step  = 0x0A;
    }
    beat = g_FrameCount / 5;
    if (g_FrameCount == beat * 5) {
        func_801F4E70(beat & 3);
    }
    func_801F49A0(0);
    func_801F49A0(1);
    func_801F482C();
}
