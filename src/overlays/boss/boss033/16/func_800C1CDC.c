#include "boss033_16.h"

MATCH void func_800C1CDC(void) {
    if (g_BattleCurrentEnemy->hp == 0xFFFF) {
        g_BattleActionType = 3;
        TASK_BYTES[4]      = 0;
    }
}
