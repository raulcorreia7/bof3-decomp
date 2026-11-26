#include "area174_13.h"

MATCH void func_801F2CA8(void) {
    s32 result;

    if (!(SELF(Actor)->timer & 0x7)) {
        result = func_801F2E88();
        if (result != 0) {
            func_801F3378(result);
        }
    }
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->unk_06 != 0) {
        Area_UpdateShots();
    }
    if (g_PartyActors[0].pos.x.fixed == TO_COORD(60) + COORD_HALF) {
        SELF(Actor)->header.mode += 1;
    }
}
