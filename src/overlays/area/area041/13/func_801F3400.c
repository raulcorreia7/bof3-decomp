#include "area041_13.h"

MATCH void func_801F3400(void) {
    func_801F387C(D_801F4308[g_SpadWork->unk_09] << 4);
    g_SpadWork->unk_09 += 1;
    if (g_SpadWork->unk_09 >= 0x29U) {
        SND_PlayCue(0x205);
        g_SpadWork->unk_09         = 0;
        g_SpadWork->z.part.integer = -0x88;
        g_SpadWork->state_02 += 1;
    }
}
