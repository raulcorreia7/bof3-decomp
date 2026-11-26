#include "boss036_16.h"

/* func_800C1FA4 */
MATCH void Effect_AddActor(void) {
    Script_AnimStepLoop();
    Area_AddActor();
    if (g_Battle.flags & BATTLE_STATE_EFFECT_PLAYING) {
        SELF(Actor)->header.step++;
    }
}
