#include "battle_15.h"

MATCH void func_800A8610(void) {
    if (func_801DEE4C() & 0xFF) {
        Actor_SelectScript((BATTLE_WORK->facing + 0x3C) & 0xFF);
        BATTLE_WORK->header.mode++;
    }
}
