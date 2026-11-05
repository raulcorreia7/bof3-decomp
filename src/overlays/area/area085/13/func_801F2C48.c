#include "area085_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    g_SpadWork->unk_09      = 0xC;
    g_SpadWork->unk_01      = 1;
    g_SpadWork->state_02    = 0;
    work                    = g_SpadWork;
    work->tint.bytes.unk_5F = 0;
    work->tint.bytes.unk_5E = 0;
    work->tint.bytes.unk_5D = 0;
    func_801F2ED8();
    func_801F2FCC();
}
