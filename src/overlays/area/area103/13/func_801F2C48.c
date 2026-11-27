#include "area103_13.h"

MATCH void func_801F2C48(void) {
    func_801F349C();
    SELF(Actor)->timer  = 128;
    SELF(Actor)->unk_0A = 0;
    SELF(Actor)->header.mode++;
    SND_SEPlay(512);
    SND_SEPlay(522);
}
