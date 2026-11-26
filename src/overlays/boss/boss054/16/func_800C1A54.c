#include "boss054_16.h"

MATCH void func_800C1A54(void) {
    PartyMember* saved;

    saved  = SELF(PartyMember);
    g_Self = D_801EC2E0->target.party;
    Script_Select(2);
    g_Self        = saved;
    saved->unk_0C = 8;
    saved->header.mode++;
}
