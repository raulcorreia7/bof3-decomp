#include "battle_15.h"

/* @increments the global counter at g_BattleUIState if D_801485E0 equals 0xA3.
 */
MATCH void func_800A60A8(void) {
    s16*         state;
    volatile u8* counter;

    state = (s16*)&D_801485E0;
    if (*state == 0xA3) {
        counter  = &g_BattleUIState;
        *counter = *counter + 1;
    }
}
