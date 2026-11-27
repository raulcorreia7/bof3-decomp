#include "battle_03.h"

MATCH void func_801E4FA8(void) {
    PartyMember* work;

    SELF(PartyMember)->unk_18 = -ONE;
    SELF(PartyMember)->unk_1C = 0;
    func_801DD3CC(SELF(void));
    work                     = SELF(PartyMember);
    work->facing             = work->facing ^ 0x2;
    work                     = SELF(PartyMember);
    work->unk_0C             = 0;
    work->unk_10             = 0;
    work->unk_09             = 0x10;
    SELF(PartyMember)->timer = 8;
    Battle_RequestEnemyScript(0);
    GFX_PaletteAllocFade(SELF(void), -4, -4, -4, 1);
    work                      = SELF(PartyMember);
    work->header.flags        = work->header.flags | ACTOR_FLAG_SEMI_TRANSPARENT;
    SELF(PartyMember)->unk_5C = 2;
    SELF(PartyMember)->unk_5D = 0;
    SELF(PartyMember)->unk_5E = 0;
    SELF(PartyMember)->unk_5F = 0;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
    Battle_IsEnemyBlocked();
    work              = SELF(PartyMember);
    work->header.step = work->header.step + 1;
}
