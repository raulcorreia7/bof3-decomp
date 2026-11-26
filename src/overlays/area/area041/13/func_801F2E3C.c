#include "area041_13.h"

MATCH void func_801F2E3C(void) {
    SELF(Actor)->timer++;
    SELF(Actor)->pos.y.fixed += 8;
    if (SELF(Actor)->timer >= 32) {
        SELF(Actor)->header.step++;
        Area_CellSetCode(41, D_801F42C8[SELF(Actor)->param.unk_0B], 0);
        Area_CellSetCode(41, D_801F42C8[SELF(Actor)->param.unk_0B] + 1, 0);
    }
    func_801F2EFC();
}
