#include "boss033_16.h"
#include "area/spad.h"

MATCH void func_800C1CDC(void) {
    if (g_BattleCurrentEnemy->hp == 65535) {
        g_Battle.action_type = 3;
        g_Task->unk_04       = 0;
    }
}
