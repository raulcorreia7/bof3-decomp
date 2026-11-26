#include "boss033_16.h"

MATCH void func_800C1A58(void) {
    u8 timer;

    timer                    = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = timer;
    if (!(timer & BYTE_MASK)) {
        Battle_PlayEnemySE(*g_BattleCurrentEnemy->unk_E8);
        Battle_PlayEnemySE((*g_BattleCurrentEnemy->unk_E8 + 4) & HALF_MASK);
        SELF(PartyMember)->header.step += 1;
    }
}
