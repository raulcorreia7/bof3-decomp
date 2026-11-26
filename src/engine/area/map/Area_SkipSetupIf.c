#include "engine/game/00/game_00.h"

/* func_801A4798 */
/* Steps over a 0xF0 or 0xF1 block. */
MATCH u8* Area_SkipSetupIf(u8* script) {
    u8 value;

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
