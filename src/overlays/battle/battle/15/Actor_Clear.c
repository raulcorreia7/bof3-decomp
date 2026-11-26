#include "battle_15.h"

/* func_800ACFF4 */
MATCH void Actor_Clear(void) {
    SELF(PartyMember)->header.flags = 0;
    SELF(PartyMember)->header.mode  = 0;
    SELF(PartyMember)->header.step  = 0;
    SELF(PartyMember)->unk_03       = 0;
    SELF(PartyMember)->unk_04       = 0;
}
