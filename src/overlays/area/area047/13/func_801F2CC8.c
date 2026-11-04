#include "area047_13.h"

MATCH void func_801F2CC8(void) {
    Actor* work;

    func_801F31F4(0x80);
    func_801F330C();
    if ((g_FrameCount & 7) == 0) {
        func_801F32C4();
    }
    work = g_SpadWork;
    if (--work->unk_0C == 0) {
        work->unk_0C = 0x10;
        work->unk_01++;
    }
}
