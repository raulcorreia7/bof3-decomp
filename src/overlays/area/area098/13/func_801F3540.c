#include "area098_13.h"

MATCH void func_801F3540(void) {
    func_801F40A4();
    TASK(Actor)->timer  = 255;
    TASK(Actor)->unk_0A = 0;
    TASK(Actor)->unk_06 = 16;
    TASK(Actor)->header.mode++;
    SND_SEPlay(516);
}
