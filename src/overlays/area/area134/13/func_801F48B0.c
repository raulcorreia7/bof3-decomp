#include "area134_13.h"

MATCH void func_801F48B0(void) {
    AreaSlotRecord* record;

    record = (AreaSlotRecord*)func_801F4938();
    if (record == NULL) {
        return;
    }
    record->active      = g_Task->unk_06;
    record->unk_01      = 0;
    record->unk_02      = 0;
    record->unk_03      = 0x80;
    record->unk_04      = 0x80;
    record->pos.x.fixed = g_Task->pos.x.fixed;
    record->pos.y.fixed = g_Task->pos.y.fixed;
    record->pos.z.fixed = 0;
    record->unk_18      = 0x1800;
    record->unk_1C      = 0;
    record->unk_20      = 0;
}
