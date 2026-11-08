#include "commu00_00.h"

MATCH void func_801F0E1C(u8 task_index, u8 record_kind_index) {
    if (D_801F2928[record_kind_index] == 0) {
        g_Task->unk_06                          = 5;
        g_Task->unk_18                          = 1;
        g_Task->unk_1C                          = 1;
        g_Actors[task_index & BYTE_MASK].unk_7C = 0xCA;
    } else {
        g_Task->unk_06                          = 1;
        g_Actors[task_index & BYTE_MASK].unk_7C = (D_801F2928[record_kind_index] | 0xC000);
    }
}
