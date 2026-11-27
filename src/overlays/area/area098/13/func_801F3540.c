#include "area098_13.h"

MATCH void func_801F3540(void) {
    func_801F40A4();
    SELF(Actor)->timer  = 255;
    SELF(Actor)->unk_0A = 0;
    SELF(Actor)->unk_06 = 16;
    SELF(Actor)->header.mode++;
    SND_SEPlay(516);
}
