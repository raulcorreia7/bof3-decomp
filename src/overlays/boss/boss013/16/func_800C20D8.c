#include "boss013_16.h"

MATCH void func_800C20D8(void) {
    g_BattleChooseEndingHook = func_800C2348;
    g_BattleEndHook          = func_800C243C;
    g_BossBattleEventHook    = func_800C2138;
    D_800C26E0               = RANDOM_MASK(2) + 8;
}
