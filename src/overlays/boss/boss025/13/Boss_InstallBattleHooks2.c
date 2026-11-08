#include "boss025_13.h"

MATCH void Boss_InstallBattleHooks2(void) {
    g_Battle.choose_ending_hook = Boss_ChooseBattleEnding2;
    g_Battle.end_hook           = Boss_EndBattle2;
    g_Battle.boss_event_hook    = Boss_HandleBattleEvent2;
    D_801FE4F0                  = 0;
    D_801FE4E8                  = 0;
    D_801FE4EF                  = 0;
}
