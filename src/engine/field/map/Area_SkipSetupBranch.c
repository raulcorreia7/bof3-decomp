#include "engine/game/00/game_00.h"

/* func_801A44A4 */
/* Steps over a control record without running it. */
MATCH u8* Area_SkipSetupBranch(u8* script) {
    switch (script[0]) {
        case 0xF0:
        case 0xF1:
            script = Area_SkipSetupIf(script);
            break;
        case 0xF4:
            script = Area_SkipSetupIfChain(script);
            break;
        case 0xF9:
            script++;
            /* fallthrough */
        case 0xFA:
            script++;
            break;
    }
    return script;
}
