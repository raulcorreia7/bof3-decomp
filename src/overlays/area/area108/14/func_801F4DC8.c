#include "area108_14.h"

MATCH void func_801F4DC8(void) {
    ActorSlot* slot;
    u8         value;

    g_SpadWork->unk_0B = Actor_FindFreeSlot();
    value              = g_SpadWork->unk_0B;
    if (value != 0xFF) {
        slot           = &g_ActorSlots[value];
        slot->x.fixed  = 0x158000;
        slot->flags_00 = 1;
        slot->type     = 0x51;
        slot->unk_01   = 0xA;
        slot->y.fixed  = 0x418000;
        slot->z.fixed  = Area_SampleHeight(slot->x.fixed, 0x418000) << 0x10;
        return;
    }
    g_ScriptState->cursor -= 2;
}
