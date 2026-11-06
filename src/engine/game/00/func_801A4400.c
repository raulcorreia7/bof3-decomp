#include "game_00.h"

MATCH u8* func_801A4400(u8* script) {
    u8 value;

    switch (script[0]) {
        case 0xF0:
            script = ((u8 * (*)(u8*)) func_801A3FC0)(script + 1);
            break;
        case 0xF1:
            script = ((u8 * (*)(u8*)) func_801A4158)(script + 1);
            break;
        case 0xF4:
            script = func_801A4518(script + 1);
            break;
        case 0xF9:
            value = script[1];
            script += 2;
            (*(s16*)&D_8014820C) = value;
            break;
        case 0xFA:
            value = LOBU(g_SceneState.scenario_id);
            script += 1;
            (*(s16*)&D_8014820C) = (s8)value;
            break;
    }
    return script;
}
