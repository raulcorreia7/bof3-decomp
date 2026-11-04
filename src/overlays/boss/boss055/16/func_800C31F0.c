#include "boss055_16.h"

MATCH void func_800C31F0(void) {
    if (func_801E3160() & 0xFF) {
        D_801EB4E0->unk_02 += 1;
        func_801E5988();
        return;
    }
    Area_AddActor();
    func_800C3284();
}
