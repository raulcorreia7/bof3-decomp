#include "battle_15.h"

MATCH void func_800A8540(void) {
    D_800B50B0[SELF(PartyMember)->header.mode]();
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}
