#include "area103_13.h"

MATCH void func_801F2C48(void) {
    func_801F349C();
    TASK(Actor)->timer  = 128;
    TASK(Actor)->unk_0A = 0;
    TASK(Actor)->header.mode++;
    SND_SEPlay(512);
    SND_SEPlay(522);
}
