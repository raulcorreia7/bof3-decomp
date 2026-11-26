#include "boss055_16.h"

MATCH void func_800C1B08(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        Battle_PlayEnemySE(*g_BattleCurrentEnemy->unk_E8);
    }
    SELF(PartyMember)->param.unk_0B = 0;
}
