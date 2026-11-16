#include "boss018_16.h"

MATCH void Boss_EndBattle2(void) {
    u8* row;

    row = D_801EB6B2;
    if ((*(u16*)row & 0x4000) == 0) {
        Battle_CopyActorEntry(1, (PartyMember*)(row - 0x82), 1);
        Battle_ShowActorEntry(1);
    }
    Battle_CopyActorEntry(3, (PartyMember*)(row + 0x96), 0);
    Battle_ShowActorEntry(3);
    Battle_CopyActorEntry(4, (PartyMember*)(row + 0x1AE), 0);
    Battle_ShowActorEntry(4);
}
