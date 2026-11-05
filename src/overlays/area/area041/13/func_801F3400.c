#include "area041_13.h"

MATCH void func_801F3400(void) {
    func_801F387C(D_801F4308[g_Task->unk_09] << 4);
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 0x29U) {
        SND_PlayCue(0x205);
        g_Task->unk_09       = 0;
        COORD_INT(g_Task->z) = -0x88;
        g_Task->step += 1;
    }
}
