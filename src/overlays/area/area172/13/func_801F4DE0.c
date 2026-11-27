#include "area172_13.h"

MATCH void func_801F4DE0(void) {
    Actor* work;
    u16    screen_x;
    u8*    counter;

    work           = SELF(Actor);
    screen_x       = work->screen_x + 0xA;
    work->screen_x = screen_x;
    if ((s16)screen_x >= 0x191) {
        counter = &g_ScenarioState.step;
        *counter += 1;
        work->header.mode = 2;
    }
    func_801F4E8C(220, 200);
    func_801F4F70((s16)SELF(Actor)->screen_x, 0xC8);
}
