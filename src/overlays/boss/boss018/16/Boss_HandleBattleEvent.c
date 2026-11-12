#include "boss018_16.h"

#include "Boss_TallyPartDefeatsBody.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    BOSS_TALLY_PART_DEFEATS_BODY();
    return 0;
}
