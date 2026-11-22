#include "battle_15.h"

MATCH void func_800A8C60(void) {
    D_800B50CC[TASK(PartyMember)->header.mode]();
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}
