#include "battle_15.h"

/* func_800ACFF4 */
MATCH void Actor_Clear(void) {
    TASK(PartyMember)->header.flags = 0;
    TASK(PartyMember)->header.mode  = 0;
    TASK(PartyMember)->header.step  = 0;
    TASK(PartyMember)->unk_03       = 0;
    TASK(PartyMember)->unk_04       = 0;
}
