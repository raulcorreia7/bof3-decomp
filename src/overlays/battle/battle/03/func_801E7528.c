#include "battle_03.h"

MATCH void func_801E7528(void) {
    u8* work;

    g_BattleEffectBattler->unk_48 = 2;
    work                          = *(void**)(SP(0x44u)) + 1;
    *work                         = (*work + 1);
}
