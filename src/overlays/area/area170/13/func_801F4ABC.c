#include "area170_13.h"

MATCH void func_801F4ABC(void) {
    s8* mode;

    mode = &D_801448EB;
    if (*mode == 0x33) {
        *mode = 0x25;
    }
    func_801F3994();
    if (D_80143F06 == 2) {
        if (D_80143F03 == 1) {
            SND_PlayCue(0x20C);
        }
    }
    if (D_80143F06 == 3) {
        if (D_80143F03 == 2) {
            SND_PlayCue(0x20C);
        }
    }
}
