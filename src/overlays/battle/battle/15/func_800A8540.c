#include "battle_15.h"

MATCH void func_800A8540(void) {
    D_800B50B0[BATTLE_WORK->header.mode]();
    if (BATTLE_WORK->header.flags != 0) {
        func_8014D290();
    }
}
