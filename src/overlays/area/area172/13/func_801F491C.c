#include "area172_13.h"

MATCH void func_801F491C(void) {
    Actor* work;
    Actor* other;

    if (g_ScriptVars[0] < 7) {
        work = g_Task;
        work->pos.x.fixed += D_801F6780[work->unk_0A & 0xF] << 11;
        work->pos.y.fixed -= D_801F6780[work->unk_0A & 0xF] << 11;
        work->unk_0A--;
        FIELD(u16, g_GameState, 0x122) -= 2;
    } else {
        other = g_Task;
        other->pos.x.fixed &= ~0x7FFF;
        other->pos.y.fixed &= ~0x7FFF;
    }
}
