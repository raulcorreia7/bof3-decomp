#include "boss025_13.h"

MATCH void func_800C1F0C(void) {
    u8 count;

    func_801E30F8();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & 0xFF)) {
        Battle_PlayEffectCue(*g_BattleCurrentEnemy->unk_E8);
        g_Task->header.step += 1;
    }
}
