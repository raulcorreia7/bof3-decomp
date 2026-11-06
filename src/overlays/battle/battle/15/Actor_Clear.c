#include "battle_15.h"

/* func_800ACFF4 */
MATCH void Actor_Clear(void) {
    BATTLE_WORK->header.flags = 0;
    BATTLE_WORK->header.mode  = 0;
    BATTLE_WORK->header.step  = 0;
    BATTLE_WORK->unk_03       = 0;
    BATTLE_WORK->unk_04       = 0;
}
