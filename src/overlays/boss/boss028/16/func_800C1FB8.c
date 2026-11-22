#include "boss028_16.h"

MATCH void func_800C1FB8(void) {
    D_800C21BC[TASK(Actor)->header.step]();
    if (TASK(Actor)->header.flags & 0x1) {
        Area_AddGridActor();
    }
}
