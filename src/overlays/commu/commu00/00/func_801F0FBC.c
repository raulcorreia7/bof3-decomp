#include "commu00_00.h"

MATCH void func_801F0FBC(u8 source_index, u8 task_index, u8 record_type_index) {
    if (g_FairyJobs[source_index].record_state == 0) {
        SELF(Actor)->unk_06                     = 1;
        g_Actors[task_index & BYTE_MASK].unk_7C = 0x51;
    } else if (g_FairyJobs[source_index].record_state == 1) {
        SELF(Actor)->header.flags = 0;
    } else {
        SELF(Actor)->unk_06                     = 1;
        g_Actors[task_index & BYTE_MASK].unk_7C = 0xC004;
    }
}
