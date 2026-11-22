#include "boss055_16.h"

MATCH void func_800C20A4(void) {
    D_800C35D8[TASK(PartyMember)->header.step]();
    if (TASK(PartyMember)->header.mode == 8 && TASK(PartyMember)->header.step < 3) {
        func_800C227C();
    }
}
