#include "boss033_16.h"
#include "area/spad.h"

MATCH void func_800C1AF8(void) {
    u16* flags;

    if ((g_Task->header.flags & ACTOR_FLAG_HIDDEN) == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5704();
        func_801E567C();
    }
}
