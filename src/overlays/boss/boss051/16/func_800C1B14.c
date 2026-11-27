#include "boss051_16.h"

MATCH void func_800C1B14(void) {
    PartyMember* saved;
    PartyMember* battler;
    PartyMember* work;
    u8           type;

    SELF(PartyMember)->header.mode += 1;
    type                      = g_BattleEnemyBattlers[0].type;
    SELF(PartyMember)->unk_09 = ENCOUNTER_ENEMIES[type].unk_84[2];
    SELF(PartyMember)->timer  = 45;

    battler = g_BattleEffectBattler;
    saved   = SELF(PartyMember);
    SELF_SET(battler);
    battler->unk_24 |= 0x80;

    work         = SELF(PartyMember);
    work->unk_29 = 2;
    work->screen_x.value += 0x30;
    work->screen_y.value -= 0x10;

    Script_Select(2);
    SELF_SET(saved);
}
