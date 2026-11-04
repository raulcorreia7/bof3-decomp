#include "boss008_16.h"

MATCH void Boss_EndBattle2(void) {
    BOSS008_END_BATTLE_BEGIN(1);
    g_SpadWork->unk_2A = 1;
    BOSS008_END_BATTLE_FINISH();
}
