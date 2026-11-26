#include "boss025_13.h"

MATCH void func_800C1DCC(void) {
    EnemyBattler* work;

    work                           = g_BattleCurrentEnemy;
    work->script                   = D_800C3180;
    work->unk_E4                   = func_800C20F0;
    work->unk_E8                   = D_800C3194;
    SELF(PartyMember)->facing      = FACING_RIGHT;
    SELF(PartyMember)->header.mode = 2;
    Script_AnimStepLoop();
}
