#include "area132_13.h"

MATCH void func_801F2F98(void) {
    u8  i;
    u8* effect;

    i = 0;
    if (g_Task->param.unk_0B != 0) {
        func_801F385C();
    }
    do {
        effect = func_801F3800();
        if (effect != NULL) {
            func_801F37A4(effect);
            FIELD(u16, effect, 0x14u) = 0x80;
            FIELD(u8, effect, 0x17u) = i;
        }
        i++;
    } while (i < 0x10);
    SND_PlayCue(0x206);
    g_Task->header.step++;
}
