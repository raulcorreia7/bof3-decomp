#include "game_00.h"

MATCH void func_8019CFCC(void) {
    u8 value;

    ACTOR_COUNT_DOWN(TASK(Actor), value, timer);
    if ((value & BYTE_MASK) == 0) {
        if (LOHU(g_GameAreaId) == AREA_ID_CONTAINER_YARD) {
            SYS_SetFlag(g_SceneEventFlags, 68);
        }
        Actor_Clear();
        return;
    }
    func_8019D800();
    func_8019DC6C();
    Actor_ProjectForDraw();
}
