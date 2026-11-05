#include "area152_13.h"

MATCH void func_801F43E8(void) {
    Actor* scratch;
    u8*    work;

    scratch = g_Task;
    if (scratch->unk_0B != 0) {
        if ((scratch->flags & ACTOR_FLAG_OFFSCREEN) != 0) {
            Actor_Clear();
            return;
        }
    } else if ((scratch->flags & ACTOR_FLAG_OFFSCREEN) == 0) {
        scratch->unk_0B = 1;
    }

    work = (u8*)g_Task;
    *(s32*)(work + 0x34) += *(s32*)(work + 0x0C);
    *(s32*)(work + 0x38) += *(s32*)(work + 0x10);
    func_8014D978();
    func_8014D290();
}
