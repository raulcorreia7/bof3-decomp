#include "commu00_00.h"

MATCH void func_801F1254(u8 task_index) {
    g_Task->unk_06                          = 1;
    g_Actors[task_index & BYTE_MASK].unk_7C = 0xC00A;
}
