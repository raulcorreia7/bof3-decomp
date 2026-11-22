#include "boss033_16.h"

MATCH void func_800C1A58(void) {
    u8 timer;

    timer                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer;
    if (!(timer & BYTE_MASK)) {
        Battle_PlayEnemySE(*g_BattleCurrentEnemy->unk_E8);
        Battle_PlayEnemySE((*g_BattleCurrentEnemy->unk_E8 + 4) & HALF_MASK);
        TASK(PartyMember)->header.step += 1;
    }
}
