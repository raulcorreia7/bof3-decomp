#include "area168_13.h"

MATCH void func_801F3DB0(void) {
    Actor* scratch;
    Actor* work;

    scratch = g_SpadWork;
    scratch->direction_08 = 1;
    /* FAKE: retail splits the re-read across the copy so the row stays in
     * one register. */
    work = g_SpadWork;
    scratch = work;
    scratch->state_02++;
    scratch->z.part.integer = 0;
    scratch->gravity = 0x28709126;
    scratch->unk_30 = 0;
    func_801F4158_area168(0, 1);
    func_801F4158_area168(1, 2);
}
