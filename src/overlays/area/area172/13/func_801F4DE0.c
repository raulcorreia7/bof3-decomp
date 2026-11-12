#include "area172_13.h"

MATCH void func_801F4DE0(void) {
    Actor* work;
    u16    screen_x;
    u8*    counter;

    work           = g_Task;
    screen_x       = work->screen_x + 0xA;
    work->screen_x = screen_x;
    if ((s16)screen_x >= 0x191) {
        counter = &g_SceneState.step_05;
        *counter += 1;
        work->header.mode = 2;
    }
    func_801F4E8C(220, 200);
    func_801F4F70((s16)g_Task->screen_x, 0xC8);
}
