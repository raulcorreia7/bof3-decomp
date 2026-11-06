#include "boss055_16.h"

MATCH void func_800C2E04(void) {
    if (func_801E3160() & 0xFF) {
        D_801EB4E0->header.mode += 1;
        D_801EB4E0->header.step = 0;
        func_801E5988();
        return;
    }
    Area_AddActor();
    func_800C3284();
}
