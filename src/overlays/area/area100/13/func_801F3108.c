#include "area100_13.h"

MATCH void func_801F3108(void) {
    Actor* actor = SELF(Actor);
    Pos3   pos;

    actor->gravity += 0x100000;
    actor->vz += actor->gravity;
    pos.x = actor->pos.x.fixed;
    pos.y = actor->pos.y.fixed;
    pos.z = actor->pos.z.fixed;
    func_801F31E8(&pos, actor->vz);
    if (SELF(Actor)->vz > 0x07FFFFFF) {
        SELF(Actor)->header.mode++;
    }
}
