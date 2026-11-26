#include "boss055_16.h"

MATCH void func_800C28E0(void) {
    Area_SceneSelectRecord(0x30C);
    SELF(Actor)->unk_48       = 0;
    SELF(Actor)->active_flags = 0;
    SELF(Actor)->pos.z.fixed  = 0;
    func_800C2948();
    SELF(PartyMember)->header.step++;
}
