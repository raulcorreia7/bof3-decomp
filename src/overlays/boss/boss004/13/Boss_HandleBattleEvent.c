#include "boss004_13.h"

#include "overlays/boss/Boss_HandleBattleEventBody.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    BOSS_HANDLE_BATTLE_EVENT_BODY();
    return 0;
}
