#include "boss025_13.h"

MATCH void func_800C1F0C(void) {
    u8 count;

    func_801E30F8();
    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (!(count & 0xFF)) {
        func_801E52F0(*g_BattleCurrentEnemy->unk_E8);
        g_SpadWork->unk_02 += 1;
    }
}
