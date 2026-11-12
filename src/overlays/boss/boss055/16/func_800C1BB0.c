#include "boss055_16.h"

MATCH void func_800C1BB0(void) {
    Battle_MarkDamaged(g_Battle.target_selector);
    g_Task->header.step++;
}
