#include "engine/game/00/game_00.h"

/* func_801A4798 */
/* Steps over a 0xF0 or 0xF1 block. */
MATCH u8* Area_SkipSetupIf(u8* script) {
    u8 value;

    /* The barrier keeps the +3 cursor bump below the callee-save stores.
     * Without it gcc-2.7.2's post-reload scheduler moves the bump above them;
     * the retail order reappears with -fno-schedule-insns2, which no flag
     * profile provides (200-combo probe: no exact).
     */
    /* FAKE: FAKE_BARRIER holds the retail store order. */
    FAKE_BARRIER();
    script += 3;
    value = *script;
    while (value != 0xFE) {
        if (value >= 0xF0) {
            if (value < 0xFD) {
                script = Area_SkipSetupBranch(script);
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
