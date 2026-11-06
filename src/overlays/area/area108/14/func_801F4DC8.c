#include "area108_14.h"

MATCH void func_801F4DC8(void) {
    ActorSlot* slot;
    u8         value;

    g_Task->unk_0B = Actor_FindFreeSlot();
    value          = g_Task->unk_0B;
    if (value != 0xFF) {
        slot               = &g_ActorSlots[value];
        slot->pos.x.fixed  = TO_COORD(21) + COORD_HALF;
        slot->header.flags = 1;
        slot->type         = 0x51;
        slot->header.mode  = 0xA;
        slot->pos.y.fixed  = TO_COORD(65) + COORD_HALF;
        slot->pos.z.fixed  = Area_SampleHeight(slot->pos.x.fixed, TO_COORD(65) + COORD_HALF) << 0x10;
        return;
    }
    g_ScriptState->cursor -= 2;
}
