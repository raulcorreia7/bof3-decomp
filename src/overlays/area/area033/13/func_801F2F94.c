#include "area033_13.h"

/* Each access reloads the work cell through g_Task. */
MATCH void func_801F2F94(void) {
    g_Task->active_flags = 0x80;
    Area_FindSceneRecord(0xF);
    ((u8*)g_Task)[0x29] = 5;
    ((u8*)g_Task)[0x2A] = 0;
    ((u8*)g_Task)[0x5D] = 0;
    ((u8*)g_Task)[0x5E] = 0;
    ((u8*)g_Task)[0x5F] = 0;
    ((u8*)g_Task)[1]    = 1;
}
