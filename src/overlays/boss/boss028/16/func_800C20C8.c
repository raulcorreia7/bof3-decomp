#include "boss028_16.h"

MATCH void func_800C20C8(void) {
    if (!ACTOR_IN_USE(*D_801EB4E0)) {
        TASK_BYTES[2]++;
    }
    func_8014D978();
}
