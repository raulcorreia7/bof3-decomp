#include "area048_13.h"

MATCH void func_801F4864(void) {
    u8* counter;

    g_CurrentActor->flags_74 &= 0xFE;
    if (g_CharSlot[D_80145F09] == 1) {
        counter = &D_8014686B;
        if (*counter < 8U) {
            *counter += 1;
        }
        SND_PlayCue(0x20DU);
    }
}
