#include "area047_13.h"

MATCH void func_801F2CC8(void) {
    Actor* work;

    func_801F31F4(0x80);
    func_801F330C();
    if ((g_FrameCount & 7) == 0) {
        func_801F32C4();
    }
    work = g_Task;
    if (--work->vx == 0) {
        work->vx = 0x10;
        work->mode++;
    }
}
