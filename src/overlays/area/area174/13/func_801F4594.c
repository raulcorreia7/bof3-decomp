#include "area174_13.h"

MATCH void func_801F4594(void) {
    Actor* work;
    Actor* other;
    u8*    record;

    record = (u8*)(g_GameState->u.field.index_124);
    record += g_ScriptState->cursor;
    if (g_ScriptVars[0] < record[2]) {
        work = g_Task;
        work->pos.x.fixed += D_801F6754[work->unk_0A & 0xF] << 11;
        work->pos.y.fixed -= D_801F6754[work->unk_0A & 0xF] << 11;
        work->unk_0A--;
        g_GameState->u.field.unk_122 -= 2;
    } else {
        other = g_Task;
        other->pos.x.fixed &= ~0x7FFF;
        other->pos.y.fixed &= ~0x7FFF;
        g_ScriptState->cursor++;
    }
}
