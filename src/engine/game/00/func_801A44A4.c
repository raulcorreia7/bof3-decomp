#include "game_00.h"

MATCH u8* func_801A44A4(u8* script) {
    switch (script[0]) {
        case 0xF0:
        case 0xF1:
            script = func_801A4798(script);
            break;
        case 0xF4:
            script = func_801A4844(script);
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
