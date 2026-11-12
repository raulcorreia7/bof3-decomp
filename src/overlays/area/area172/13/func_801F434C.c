#include "area172_13.h"

MATCH void func_801F434C(void) {
    u8 size;
    u8 i;

    size = g_Game.party_size;
    i    = 0;
    if (size != 0) {
        do {
            if (g_Game.members[i].chr.character_id == CHAR_ID_REI) {
                g_ScriptState->cursor += 3;
                return;
            }
            i += 1;
        } while (i < size);
    }
}
