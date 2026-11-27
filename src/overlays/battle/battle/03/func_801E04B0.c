#include "battle_03.h"

MATCH void func_801E04B0(void) {
    PartyMember* enemy_work;
    PartyMember* work;

    enemy_work = g_Game.current;
    if (HAS_STATUS(*enemy_work, STATUS_KO)) {
        SELF(PartyMember)->unk_03 = 2;
        SELF(PartyMember)->timer  = 0;
        return;
    }
    work                                = SELF(PartyMember);
    *(u16*)(((u32)enemy_work + 0x11Cu)) = 0;
    work->unk_0C                        = 0;
    work->unk_10                        = -0x2000;
    Effect_RotatePosition(work);
    SELF(PartyMember)->timer = 4;
    Battle_IsPartyMemberBlocked();
    SND_SEQueueSelection(0x205);
    SELF(PartyMember)->unk_03 += 1;
}
