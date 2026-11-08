#include "area082_13.h"

MATCH void func_801F5594(void) {
    u8 slot;

    slot = g_Game.current->chr.character_id;
    if (slot != 8) {
        if (slot == 4) {
            g_ScriptState->cursor += 0xA;
        } else {
            g_ScriptState->cursor += 0x16;
        }
    }
}
