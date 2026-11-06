#include "commu00_00.h"

MATCH void func_801F1204(u8 task_index, u8 record_kind_index) {
    g_Task->unk_06              = 1;
    g_Actors[task_index].unk_7C = (D_801F2928[record_kind_index] + 0xC005);
}
