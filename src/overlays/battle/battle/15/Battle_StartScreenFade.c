#include "battle_15.h"

/* Starts the battle screen fade. */
/* func_800AE390 */
MATCH void Battle_StartScreenFade(void) {
    PartyMember* work;

    SELF(PartyMember)->unk_09 = 0;
    work                      = SELF(PartyMember);
    work->header.mode         = (work->header.mode + 1);
}
