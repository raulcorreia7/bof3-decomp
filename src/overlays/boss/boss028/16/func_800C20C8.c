#include "boss028_16.h"

MATCH void func_800C20C8(void) {
    if (!ACTOR_IN_USE(*D_801EB4E0)) {
        SPAD_WORK_BYTES[2]++;
    }
    func_8014D978();
}
