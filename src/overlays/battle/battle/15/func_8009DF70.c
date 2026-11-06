#include "battle_15.h"

MATCH void func_8009DF70(void) {
    ((s16*)g_BattleTargetRecord)[2] = -5;
    if ((rand() & 0x7F) < 0x27) {
        func_800A36F0(g_BattleTarget, 0x68);
    }
}
