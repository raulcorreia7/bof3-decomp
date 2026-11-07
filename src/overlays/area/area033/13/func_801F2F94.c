#include "area033_13.h"

/* Each access reloads the work cell through g_Task. */
MATCH void func_801F2F94(void) {
    g_Task->active_flags = 0x80;
    Area_FindSceneRecord(0xF);
    TASK_BYTES[0x29]    = 5;
    TASK_BYTES[0x2A]    = 0;
    TASK_BYTES[0x5D]    = 0;
    TASK_BYTES[0x5E]    = 0;
    TASK_BYTES[0x5F]    = 0;
    g_Task->header.mode = 1;
}
