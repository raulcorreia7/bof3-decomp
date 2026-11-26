#include "boss012_16.h"

MATCH void func_800C1A24(void) {
    func_800C1C08((u16)SELF(Actor)->gravity);
    func_800C1CD8((u16)SELF(Actor)->gravity);
    SELF(Actor)->gravity += 2;
    if (SELF(Actor)->gravity == 0x56) {
        SELF(Actor)->unk_03 = 3;
    }
}
