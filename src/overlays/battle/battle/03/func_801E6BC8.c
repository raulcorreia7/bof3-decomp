#include "battle_03.h"

MATCH void func_801E6BC8(void) {
    if (Script_AnimStepLoop() != 0u) {
        g_Task->header.mode++;
        g_Task->unk_09 = 0x10;
    }
}
