#include "game_00.h"

MATCH void func_801A275C(void* unused) {
    TASK(Actor)->unk_03      = TASK(Actor)->header.mode;
    TASK(Actor)->header.mode = 5;
}
