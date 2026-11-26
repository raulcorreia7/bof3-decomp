#include "area100_13.h"

MATCH void func_801F31A0(void) {
    Pos3   pos;
    Actor* work = SELF(Actor);

    pos.x = work->pos.x.fixed;
    pos.y = work->pos.y.fixed;
    pos.z = work->pos.z.fixed;
    func_801F31E8(&pos, 0x8000000);
}
