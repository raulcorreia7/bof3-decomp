#include "area098_13.h"

MATCH void func_801F3E64(void) {
    Actor* work;

    func_801F4D44();
    work           = SELF(Actor);
    work->screen_x = 64;
    work->screen_y = 0;
    work->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
}
