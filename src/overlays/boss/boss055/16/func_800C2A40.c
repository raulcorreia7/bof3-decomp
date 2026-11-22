#include "boss055_16.h"

MATCH void func_800C2A40(void) {
    Area_SceneSelectRecord(0x30C);
    TASK(Actor)->unk_48       = 0;
    TASK(Actor)->active_flags = 0;
    TASK(Actor)->pos.z.fixed  = 0;
    func_800C2AA8();
    TASK(PartyMember)->header.step++;
}
