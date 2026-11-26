#include "area172_13.h"

MATCH void func_801F342C(void) {
    u8*    cell_1;
    u8*    cell_2;
    Actor* scratch;
    Actor* check;

    scratch = SELF(Actor);
    scratch->vx += 8;
    func_801F4060(scratch->vx);
    /* FAKE: retail splits each re-read across a cell copy so the row stays
     * in one register. */
    cell_1  = SELF(Actor);
    scratch = (Actor*)cell_1;
    scratch->timer--;
    if (scratch->timer != 0) {
        return;
    }
    cell_2          = SELF(Actor);
    scratch         = (Actor*)cell_2;
    scratch->unk_32 = 0x140;
    scratch->timer  = 16;
    check           = SELF(Actor);
    scratch->vx     = 256;
    scratch->vy     = 256;
    check->header.mode++;
    g_AreaDrawFlags = 0x1F;
}
