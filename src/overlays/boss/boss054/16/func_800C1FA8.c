#include "boss054_16.h"

MATCH void func_800C1FA8(void) {
    PartyMember* task;

    task = (PartyMember*)g_Task;
    COORD_INT(task->pos.z) += task->unk_14;
    task->unk_14 += task->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x180 to the raw register. */
    if (COORD_INT(task->pos.z) < ((s32 (*)(s32, s32))Area_SampleHeight)(task->pos.x.fixed, task->pos.y.fixed) + 0x180) {
        ((PartyMember*)g_Task)->header.step++;
    }
}
