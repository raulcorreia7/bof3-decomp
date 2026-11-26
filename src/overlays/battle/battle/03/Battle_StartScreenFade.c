#include "battle_03.h"

/* func_801E6990 */
MATCH void Battle_StartScreenFade(void) {
    PartyMember* work;

    SELF(PartyMember)->unk_09 = 0;
    work                      = SELF(PartyMember);
    work->header.mode++;
}
