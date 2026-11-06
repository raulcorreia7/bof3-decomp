#include "commu00_00.h"

MATCH void func_801F0FBC(u8 source_index, u8 task_index, u8 record_kind_index) {
    if (g_FairyJobs[source_index].record_state == 0) {
        g_Task->unk_06                                   = 1;
        D_80146904[(task_index & 0xFF) * ACTOR_SIZE / 2] = 0x51;
    } else if (g_FairyJobs[source_index].record_state == 1) {
        g_Task->header.flags = 0;
    } else {
        g_Task->unk_06                                   = 1;
        D_80146904[(task_index & 0xFF) * ACTOR_SIZE / 2] = 0xC004;
    }
}
