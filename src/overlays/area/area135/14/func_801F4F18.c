#include "area135_14.h"

extern u8 D_801F6B74[];

MATCH void func_801F4F18(void) {
    s16    slot;
    Actor *old;

    g_ScriptState->cursor -= 2;
    slot = Actor_FindFree();
    *(s16 *)0x1F800000 = slot;
    if (slot == 0xFF) {
        return;
    }
    func_801F5F28();
    old = g_Task;
    func_801A7330(&D_801F6B74[g_SceneEventSelection * 13]);
    g_Task->pos.x = old->pos.x;
    g_Task->pos.y = old->pos.y;
    g_Task->pos.z = old->pos.z;
    g_Task = old;
    func_8019F75C();
    g_Task->unk_0A = g_Task->timer;
    g_Task->timer = 0;
    g_Task->unk_04++;
}
