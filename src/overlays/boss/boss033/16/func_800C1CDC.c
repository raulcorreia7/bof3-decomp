#include "boss033_16.h"

MATCH void func_800C1CDC(void) {
    if (g_BattleCurrentEnemy->hp == 65535) {
        g_Battle.action_type = 3;
        SELF(Actor)->unk_04  = 0;
    }
}
