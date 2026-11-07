#include "area172_13.h"

MATCH void func_801F434C(void) {
    u8 size;
    u8 i;

    size = g_PartySize;
    i    = 0;
    if (size != 0) {
        do {
            if (g_BattlePartyBattlers[i].chr.character_id == 4) {
                g_ScriptState->cursor += 3;
                return;
            }
            i += 1;
        } while (i < size);
    }
}
