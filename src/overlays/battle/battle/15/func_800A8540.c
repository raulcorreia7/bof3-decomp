#include "battle_15.h"

MATCH void func_800A8540(void) {
    D_800B50B0[TASK(PartyMember)->header.mode]();
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}
