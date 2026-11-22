#include "battle_03.h"

/* func_801E6990 */
MATCH void Battle_StartScreenFade(void) {
    PartyMember* work;

    TASK(PartyMember)->unk_09 = 0;
    work                      = TASK(PartyMember);
    work->header.mode++;
}
