#include "boss008_16.h"

MATCH void func_800C2280(void) {
    g_Battle.choose_ending_hook = Boss_ChooseBattleEnding4;
    g_Battle.end_hook           = Boss_EndBattle4;
    g_Battle.boss_event_hook    = Boss_HandleBattleEvent4;
}
