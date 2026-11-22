#include "area041_13.h"

MATCH void func_801F2E3C(void) {
    TASK(Actor)->timer++;
    TASK(Actor)->pos.y.fixed += 8;
    if (TASK(Actor)->timer >= 32) {
        TASK(Actor)->header.step++;
        Area_CellSetCode(41, D_801F42C8[TASK(Actor)->param.unk_0B], 0);
        Area_CellSetCode(41, D_801F42C8[TASK(Actor)->param.unk_0B] + 1, 0);
    }
    func_801F2EFC();
}
