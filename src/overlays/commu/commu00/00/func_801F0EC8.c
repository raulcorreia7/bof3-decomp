#include "commu00_00.h"

MATCH void func_801F0EC8(u8 task_index) {
    g_Task->unk_06                                        = 1;
    D_80146904[(task_index & BYTE_MASK) * ACTOR_SIZE / 2] = 0xC003;
}
