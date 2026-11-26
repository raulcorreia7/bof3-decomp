#include "area068_13.h"

MATCH void func_801F2C48(void) {
    void** scratchpad;
    Actor* work;

    scratchpad        = SP_PTR(void*, 0u);
    work              = scratchpad[0x44u / sizeof(void*)];
    work->timer       = 0xB4;
    work              = SELF(Actor);
    work->header.mode = 1;
}
