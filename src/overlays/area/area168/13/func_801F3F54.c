#include "area168_13.h"

MATCH void func_801F3F54(void) {
    Actor* scratch;

    scratch = g_SpadWork;
    scratch->unk_30 += 0x10;
    if ((s16)scratch->unk_30 >= 0x80) {
        scratch->state_02++;
    }
    func_801F4158_area168(0, 0);
    func_801F4158_area168(1, 3);
}
