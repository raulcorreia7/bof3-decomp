#include "boss025_13.h"

MATCH void func_800C1F0C(void) {
    u8 temp_v0;

    func_801E30F8();
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_801E52F0(*g_BattleCurrentEnemy->unk_E8);
        g_SpadWork->unk_02 += 1;
    }
}
