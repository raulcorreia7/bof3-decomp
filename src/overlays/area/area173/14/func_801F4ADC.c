#include "area173_14.h"

MATCH void func_801F4ADC(void) {
    s32 actor_index;
    s32 offset;

    actor_index = Actor_FindFreeSlot() & 0xFF;
    if (actor_index != 0xFF) {
        offset                       = actor_index * sizeof(ActorSlot);
        *((u8*)g_ActorSlots + offset) = ACTOR_FLAG_IN_USE;
        D_80143FCD[offset]           = 0x9D;
        *(s16*)(D_80143FF6 + offset) = 0xC;
        D_80143FCE[offset]           = 0;
        *(s16*)(D_80143FF8 + offset) = 0xA5;
        D_80143FD3[offset]           = g_CurrentActor - g_Actors;
    }
}
