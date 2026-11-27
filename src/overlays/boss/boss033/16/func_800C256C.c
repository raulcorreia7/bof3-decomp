#include "boss033_16.h"

MATCH void func_800C256C(void) {
    D_800C27D0[SELF(Actor)->header.step]();
    if (SELF(Actor)->header.flags != 0) {
        Area_AddGridActor();
    }
}
