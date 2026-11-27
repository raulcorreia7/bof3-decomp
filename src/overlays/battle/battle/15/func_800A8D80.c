#include "battle_15.h"

MATCH void func_800A8D80(void) {
    D_800B50D4[SELF(PartyMember)->header.mode]();
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}
