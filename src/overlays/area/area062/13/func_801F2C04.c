#include "area062_13.h"

extern u8 D_80145F09;

MATCH void func_801F2C04(void) {
    Actor* actor;

    actor = g_CurrentActor;
    actor->flags_74 &= 0xFE;
    if (D_80145F09 == 6) {
        Game_SetScriptActive();
        actor      = g_CurrentActor;
        D_801448EB = 0x2A;
        D_801448EC = 0;
        do {
        } while (0); /* FAKE: the empty loop keeps the unk_7E load below the byte stores. */
        actor->unk_7E += 1;
    }
}
