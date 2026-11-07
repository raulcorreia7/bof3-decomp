#include "area098_13.h"

MATCH void func_801F3E64(void) {
    Actor* work;

    func_801F4D44();
    work           = g_Task;
    work->screen_x = 0x40;
    work->screen_y = 0;
    work->header.mode++;
    SND_PlayCue(0x200);
}
