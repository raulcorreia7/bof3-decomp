#include "area145_14.h"

MATCH u8 func_801F4CF0(u16 frame) {
    u8  result;
    s32 y;

    result = 1;
    if (frame < 5) {
        y = 4358144 - (frame << 16);
    } else {
        y = 4030464;
    }
    func_801F5190(0x428000, 0x638000, y, 0x638000);
    if (frame == 5) {
        SND_PlayCue(0x206);
    }
    if (frame >= 5) {
        result = func_801F4DA4(frame);
        if (frame >= 0x38) {
            return 2;
        }
    }
    return result;
}
