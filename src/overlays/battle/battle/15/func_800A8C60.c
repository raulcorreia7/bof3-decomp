#include "battle_15.h"

MATCH void func_800A8C60(void) {
    D_800B50CC[SELF(PartyMember)->header.mode]();
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}
