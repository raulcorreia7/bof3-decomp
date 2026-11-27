#include "battle_03.h"

MATCH void func_801E019C(void) {
    if (Script_AnimStepOnce() != 0u) {
        SELF(PartyMember)->unk_03 += 1u;
        if (!HAS_STATUS(*g_Game.current, STATUS_PARALYZED)) {
            func_801DEFE4();
        }
    }
}
