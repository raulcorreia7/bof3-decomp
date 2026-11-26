#include "battle_03.h"

MATCH void func_801E4FA8(void) {
    PartyMember* work;

    TASK(PartyMember)->unk_18 = -ONE;
    TASK(PartyMember)->unk_1C = 0;
    func_801DD3CC(TASK(void));
    work                     = TASK(PartyMember);
    work->facing             = work->facing ^ 0x2;
    work                     = TASK(PartyMember);
    work->unk_0C             = 0;
    work->unk_10             = 0;
    work->unk_09             = 0x10;
    TASK(PartyMember)->timer = 8;
    Battle_RequestEnemyScript(0);
    GFX_PaletteAllocFade(TASK(void), -4, -4, -4, 1);
    work                      = TASK(PartyMember);
    work->header.flags        = work->header.flags | ACTOR_FLAG_SEMI_TRANSPARENT;
    TASK(PartyMember)->unk_5C = 2;
    TASK(PartyMember)->unk_5D = 0;
    TASK(PartyMember)->unk_5E = 0;
    TASK(PartyMember)->unk_5F = 0;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
    Battle_IsEnemyBlocked();
    work              = TASK(PartyMember);
    work->header.step = work->header.step + 1;
}
