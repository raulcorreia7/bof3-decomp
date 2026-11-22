#include "boss033_16.h"

MATCH void func_800C1E70(void) {
    D_800C27B4[TASK(Actor)->header.step]();
    if (TASK(Actor)->header.flags != 0) {
        Area_AddGridActor();
    }
}
