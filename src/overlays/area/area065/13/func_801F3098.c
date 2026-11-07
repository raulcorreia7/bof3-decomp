#include "area065_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F3098(void) {
    g_Task->active_flags = 0x80;
    Area_FindSceneRecord(0x53);
    TASK_BYTES[0x29]    = 5;
    TASK_BYTES[0x2A]    = 0;
    TASK_BYTES[0x5D]    = 0;
    TASK_BYTES[0x5E]    = 0;
    TASK_BYTES[0x5F]    = 0;
    g_Task->header.mode = 1;
}
