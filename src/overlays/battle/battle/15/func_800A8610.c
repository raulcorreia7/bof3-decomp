#include "battle_15.h"

MATCH void func_800A8610(void) {
    if (func_801DEE4C() & BYTE_MASK) {
        Script_Select((BATTLE_WORK->facing + 0x3C) & BYTE_MASK);
        BATTLE_WORK->header.mode++;
    }
}
