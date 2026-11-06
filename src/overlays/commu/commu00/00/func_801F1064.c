#include "commu00_00.h"

MATCH void func_801F1064(u8 task_index, u8 record_kind_index) {
    if (D_801F2928[record_kind_index] != 0) {
        g_Task->unk_06                                   = 1;
        D_80146904[(task_index & 0xFF) * ACTOR_SIZE / 2] = (D_801F2928[record_kind_index] + 0xCF);
    } else {
        g_Task->unk_06                                   = 5;
        g_Task->unk_18                                   = 6;
        g_Task->unk_1C                                   = 0;
        D_80146904[(task_index & 0xFF) * ACTOR_SIZE / 2] = 0xCB;
    }
}
