#include "boss036_16.h"

MATCH void func_800C18FC(void) {
    u8 type;

    type                      = g_BattleCurrentEnemy->type;
    TASK(PartyMember)->unk_09 = MEM_PTR(u8, 0x800E40CEu)[type * 0x88u];
    Battle_RequestEnemyScript(2);
    func_801E30F8();
    TASK(PartyMember)->unk_0C = 0x4000;
    TASK(PartyMember)->unk_18 = TASK(PartyMember)->pos.x.fixed + 0x30000;
    TASK(PartyMember)->header.step++;
}
