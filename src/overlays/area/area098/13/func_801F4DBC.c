#include "area098_13.h"

MATCH void func_801F4DBC(AreaBurstSlot* slot) {
    slot->active   = 1;
    slot->life     = 8;
    slot->kind     = 0;
    slot->fade     = 0;
    slot->speed    = 0;
    slot->unk_04   = 0x20;
    slot->unk_0C   = g_Task->pos.x.fixed + ((rand() & BYTE_MASK) << 10) - 0x20000;
    slot->distance = g_Task->pos.y.fixed;
    slot->unk_14   = g_Task->pos.z.fixed + ((rand() % 0x300) << 16);
}
