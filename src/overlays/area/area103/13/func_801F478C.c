#include "area103_13.h"

MATCH void func_801F478C(void) {
    s32 beat;

    beat = TASK(Actor)->timer / 5;
    if (beat == 4) {
        Area_CellClearPalette(67, 26);
        Actor_Clear();
        return;
    }
    if (TASK(Actor)->timer % 5 == 0) {
        func_801F4E70(7 - beat);
    }
    TASK(Actor)->timer++;
}
