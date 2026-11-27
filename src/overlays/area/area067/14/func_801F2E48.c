#include "area067_14.h"

MATCH void func_801F2E48(void) {
    Pos2* vy = (Pos2*)&SELF(Actor)->vy;

    SELF(Actor)->timer = 90;
    /* FAKE: retail clears vy as two halfword stores. */
    vy->vx             = 0;
    vy->vy             = 0;
    SELF(Actor)->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
}
