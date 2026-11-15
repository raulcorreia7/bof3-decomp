#include "battle_03.h"

MATCH void func_801E4104(void) {
    if ((Battle_IsEnemyBlockedOnce() & BYTE_MASK) != 0u) {
        g_Task->unk_03 += 1u;
    }
}
