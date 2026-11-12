#include "area174_13.h"

MATCH void func_801F3E68(void) {
    u8  actor_slot;
    s32 link;

    actor_slot = Actor_FindFreeSlot();
    if (actor_slot != GAME_NONE) {
        g_ActorSlots[actor_slot].header.flags = 1;
        g_ActorSlots[actor_slot].type         = 0x9D;
        g_ActorSlots[actor_slot].unk_06       = 1;
        g_ActorSlots[actor_slot].unk_30       = 0xA5;
        link                                  = (s32)(-(((s32)g_CurrentActor - (s32)g_Actors) * 0xD79435E5)) >> 3;
        g_ActorSlots[actor_slot].link         = link;
        g_ActorSlots[actor_slot].unk_2E       = (link & BYTE_MASK) * 24 + 12;
    }
}
