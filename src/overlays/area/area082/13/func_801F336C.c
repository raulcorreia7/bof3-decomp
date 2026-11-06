#include "area082_13.h"

MATCH void func_801F336C(void) {
    Actor* actor;

    actor              = g_Task;
    actor->unk_2E      = 0x100;
    actor->unk_30      = 0;
    actor->unk_32      = 24;
    actor->header.mode = actor->header.mode + 1;
}
