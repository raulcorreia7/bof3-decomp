#include "boss012_16.h"

MATCH void func_800C1A24(void) {
    func_800C1C08((u16)TASK(Actor)->gravity);
    func_800C1CD8((u16)TASK(Actor)->gravity);
    TASK(Actor)->gravity += 2;
    if (TASK(Actor)->gravity == 0x56) {
        TASK(Actor)->unk_03 = 3;
    }
}
