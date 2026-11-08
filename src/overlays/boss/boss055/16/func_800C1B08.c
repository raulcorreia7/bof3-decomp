#include "boss055_16.h"

MATCH void func_800C1B08(void) {
    u8 timer;

    timer                          = ((PartyMember*)g_Task)->unk_09 - 1;
    ((PartyMember*)g_Task)->unk_09 = timer;
    if (timer == 0) {
        Battle_PlayEffectCue(*g_BattleCurrentEnemy->unk_E8);
    }
    ((PartyMember*)g_Task)->param.unk_0B = 0;
}
