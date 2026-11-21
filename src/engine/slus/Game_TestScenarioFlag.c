#include "engine/slus/slus.h"

/* returns bit 0 of g_ScenarioState.flags_01, inverted unless the record byte is 1.
 */
/* func_8015B6F8 */
/* Script condition: the scenario flag, inverted when the record byte is not 1. */
MATCH s32 Game_TestScenarioFlag(u8** cursor) {
    if (**cursor != 1) {
        return (g_ScenarioState.flags_01 & 0x1) ^ 0x1;
    }
    return g_ScenarioState.flags_01 & 0x1;
}
