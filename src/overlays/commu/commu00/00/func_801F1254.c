#include "commu00_00.h"

MATCH void func_801F1254(u8 task_index) {
    g_Task->unk_06                       = 1;
    D_80146904[(task_index & 0xFF) * 76] = 0xC00A;
}
