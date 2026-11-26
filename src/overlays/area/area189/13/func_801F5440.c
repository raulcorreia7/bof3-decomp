#include "area189_13.h"

MATCH void func_801F5440(void) {
    Actor* work;
    u16*   angle;

    work   = SELF(Actor);
    angle  = &D_801492DC;
    *angle = (*angle + (s8)work->param.unk_0B) & 0xFFF;
    if ((((0x12 - work->direction) & 0xF) << 8) == *angle) {
        g_Game.current->u.field.mode.value = 0;
        SELF(Actor)->header.step           = 2;
    }
}
