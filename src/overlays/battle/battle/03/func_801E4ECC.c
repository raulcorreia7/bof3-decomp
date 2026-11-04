#include "battle_03.h"

MATCH void func_801E4ECC(void) {
    if ((D_801CA71C[g_BattleActionId].mask & 0x800u) == 0u) {
        func_801E3160();
    }
    g_SpadWork->word_08.byte.unk_09 += 1u;
}
