#include "boss013_16.h"

MATCH void func_800C20D8(void) {
    g_Battle.choose_ending_hook = func_800C2348;
    g_Battle.end_hook           = func_800C243C;
    g_Battle.boss_event_hook    = func_800C2138;
    D_800C26E0                  = RANDOM_MASK(2) + 8;
}
