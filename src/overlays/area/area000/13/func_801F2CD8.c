#include "area000_13.h"
#include "area/spad.h"

MATCH void func_801F2CD8(void) {
    s32 value;

    Area_MoveActorRoute((void*)g_ScriptState, g_Task->direction_08);
    value                   = 2;
    ((u8*)g_ScriptState)[7] = value;
}
