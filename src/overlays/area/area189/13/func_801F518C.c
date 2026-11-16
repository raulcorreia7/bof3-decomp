#include "area189_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F518C(void) {
    Actor* work;
    u8*    state = &g_GameStateIndex;
    s32    x;
    s32    y;

    if ((g_Game.flags & 0x100) != 0) {
        return;
    }
    if ((g_Game.walk_flags & 0x40) != 0) {
        return;
    }
    if (*state != 0) {
        return;
    }
    if ((func_801F5D6C() & BYTE_MASK) != 0) {
        return;
    }
    if ((func_801F5EA8() & BYTE_MASK) != 0) {
        return;
    }
    switch (func_801F5F3C() & BYTE_MASK) {
        case 0:
            g_Task->timer = 0;
            func_801F5D20();
            break;
        case 1:
            g_Game.current->u.field.mode_12B.s8_value = 1;
            g_AreaCameraAngle.vz += (s8)g_Task->param.unk_0B;
            g_AreaCameraAngle.vz &= 0xFFF;
            g_Task->header.step = 4;
            break;
        case 2:
            func_801F54B0();
            work = g_Task;
            x    = work->pos.x.fixed + work->vx * work->timer;
            y    = work->pos.y.fixed + work->vy * work->timer;
            if ((u32)((x >> 24) - 0x10) < 5) {
                if ((y >> 24) >= 0x18) {
                    Message_StartAreaMessage(2);
                    *state = 2;
                    func_801F5D20();
                    break;
                }
            }
            if (SYS_TestFlag(D_80144EF8, 4) != 0 && (u32)((x >> 24) - 0x15) < 5 && (y >> 24) < 0xF) {
                Message_StartAreaMessage(3);
                *state = 2;
                func_801F5D20();
                break;
            }
            work = g_Task;
            work->timer -= 1;
            func_801F559C();
            g_Game.current->u.field.mode_12B.s8_value = 1;
            g_Task->header.step                       = 3;
            break;
    }
}
#else
INCLUDE_ASM(func_801F518C);
#endif
