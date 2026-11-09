#include "game_00.h"

MATCH u8* func_801A4798(u8* script) {
    u8 value;

    /* The barrier keeps the +3 cursor bump below the callee-save stores. */
    /* FAKE: FAKE_BARRIER holds the retail store order. */
    FAKE_BARRIER();
    script += 3;
    value = *script;
    while (value != 0xFE) {
        if (value >= 0xF0) {
            if (value < 0xFD) {
                script = func_801A44A4(script);
            }
            if (*script == 0xFD) {
                script++;
            }
        } else {
            script += s_ScriptOpcodeLengths[value >> 4];
        }
        value = *script;
    }
    return script + 1;
}
