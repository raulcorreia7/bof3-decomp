#include "area175_13.h"

MATCH void func_801F431C(void) {
    ActorSlot* slot;
    s32        index;

    index = Actor_FindFreeSlot() & 0xFF;
    if (index != 0xFF) {
        slot           = &g_ActorSlots[index];
        slot->flags_00 = 1;
        slot->type     = 0x39;
        slot->unk_2E   = (s16)g_SpadWork->unk_2E;
        slot->unk_30   = g_SpadWork->unk_30;
    }
}
