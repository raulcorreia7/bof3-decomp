#include "boss028_16.h"

/* Runs Battle_TriggerCritical and func_801E567C and raises the g_Battle.state flag 0x4 when func_801E30F8 reports a transition.
*/
MATCH void func_800C1AA0(void) {
    u16* flags;

    if (func_801E30F8() != 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        Battle_TriggerCritical();
        func_801E567C();
    }
}
