#include "boss025_13.h"

MATCH void func_800C1F0C(void) {
    u8 count;

    func_801E30F8();
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Battle_PlayEnemySE(*g_BattleCurrentEnemy->unk_E8);
        SELF(PartyMember)->header.step += 1;
    }
}
