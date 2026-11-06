#include "game_00.h"

MATCH void func_8019CFCC(void) {
    u8 value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if ((value & BYTE_MASK) == 0) {
        if (LOHU(g_GameAreaId) == 0x92u) {
            SYS_SetFlag(g_SceneEventFlags, 0x44);
        }
        Actor_Clear();
        return;
    }
    func_8019D800();
    func_8019DC6C();
    func_8015A944();
}
