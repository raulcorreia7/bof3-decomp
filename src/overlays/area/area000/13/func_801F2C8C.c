#include "area000_13.h"
#include "area/spad.h"

MATCH void func_801F2C8C(void) {
    g_Task->direction = g_CurrentActor->unk_79;
    Actor_DispatchSelectorScript(g_Task->direction);
}
