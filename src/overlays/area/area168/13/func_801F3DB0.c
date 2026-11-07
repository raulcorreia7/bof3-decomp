#include "area168_13.h"

MATCH void func_801F3DB0(void) {
    Actor* scratch;
    Actor* work;

    scratch               = g_Task;
    scratch->direction_08 = FACING_UP;
    /* FAKE: retail splits the re-read across the copy so the row stays in
     * one register. */
    work                  = g_Task;
    scratch               = work;
    scratch->header.step++;
    COORD_INT(scratch->pos.z) = 0;
    scratch->gravity          = 0x28709126;
    scratch->screen_y         = 0;
    func_801F4158_area168(0, 1);
    func_801F4158_area168(1, 2);
}
