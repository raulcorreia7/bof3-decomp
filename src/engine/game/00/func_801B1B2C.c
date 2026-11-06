#include "game_00.h"

MATCH s32 func_801B1B2C(s32 x, s32 y, s32 probe_kind, s32 flags) {
    s16    value;
    s32    mode;
    s32    px;
    s32    py;
    s32    distance;
    u8     saved;
    Actor* work;

    px           = x;
    py           = y;
    mode         = flags;
    value        = Area_ReadHeight(x, y);
    work         = g_Task;
    saved        = work->unk_09;
    work->unk_09 = 0U;
    if (func_801C3E40(px, py, mode & BYTE_MASK, value) & BYTE_MASK) {
        return 0;
    }
    distance = D_80145ECE - value;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0x41) {
        SP_REF(s32, 0x8) = px;
        SP_REF(s32, 0xC) = py;
        SP_REF(s16, 0x2) = Area_ReadHeight(px, py);
        g_Task->unk_09   = saved;
        return 1;
    }
    return 0;
}
