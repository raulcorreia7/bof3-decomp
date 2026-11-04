#include "boss008_16.h"

MATCH void Boss_EndBattle3(void) {
    BOSS008_END_BATTLE_BEGIN(2);
    g_SpadWork->unk_2A = 1;
    BOSS008_END_BATTLE_FINISH();
}
