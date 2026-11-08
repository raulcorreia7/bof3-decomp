#include "boss036_16.h"

/* func_800C1FA4 */
MATCH void Effect_AddActor(void) {
    func_8014D978();
    Area_AddActor();
    if (g_Battle.state & BATTLE_STATE_EFFECT_PLAYING) {
        TASK_BYTES[2]++;
    }
}
