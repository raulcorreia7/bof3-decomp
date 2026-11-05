#include "boss033_16.h"

MATCH void func_800C1AF8(void) {
    u16* flags;

    if ((SPAD_WORK_BYTES[0] & ACTOR_FLAG_HIDDEN) == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5704();
        func_801E567C();
    }
}
