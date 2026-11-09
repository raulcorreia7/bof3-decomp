#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801A3080(Actor* actor, s32 facing) {
    Actor* work;
    s32    slot;
    s32    type;
    s8     n;
    u8     dir;
    s16    value;
    s32    angle_x;
    s32    angle_y;
    u8*    shadow;
    u16    angle;

    slot    = (s32)(-(((s32)actor - (s32)D_80147A58) * 0xD79435E5)) >> 3;
    work    = g_Task;
    angle_x = FIELD(s32, work, 0x64u);
    angle_y = FIELD(s32, work, 0x68u);
    type    = facing;
    n       = (s8)slot;
    if (n < 0) {
        n = 4;
    }

    if (D_80147CB8[n * 0x10] & 1) {
        return;
    }

    dir = type & BYTE_MASK;
    if ((work->vx + work->vy) != 0) {
        value = (s16)(Area_SampleHeight(work->pos.x.fixed + g_FacingSteps[dir].x,
                                        work->pos.y.fixed + g_FacingStepY[dir * 2]) -
                      COORD_INT(g_Task->pos.z));
        if (facing & 2) {
            g_Task->unk_64 = 0;
            if (dir != 3) {
                value = -value;
            }
            angle_y = ratan2(value, 0x80);
        } else {
            if (dir != 1) {
                value = -value;
            }
            angle_x        = ratan2(value, 0x80);
            g_Task->unk_68 = 0;
        }
    }

    work = g_Task;
    if (FIELD(u8, work, 0x0Au) != 0) {
        D_80147CB9[n * 0x10]             = (s8)(FIELD(u8, work, 0x0Au) * 2);
        D_80147CBA[n * 0x10]             = (s8)(g_Task->unk_0A * 4);
        work                             = g_Task;
        FIELD(s32, D_80147CBC, n * 0x10) = (angle_x - FIELD(s32, work, 0x64u)) / (FIELD(u8, work, 0x0Au) * 2);
        FIELD(s32, D_80147CC0, n * 0x10) = (angle_y - FIELD(s32, work, 0x68u)) / (FIELD(u8, work, 0x0Au) * 2);
        if ((((type - 5) & BYTE_MASK) < 2) && (D_801C842A[0] < (FIELD(s32, work, 0x6Cu) & ANGLE_MASK))) {
            angle = D_801C842A[(facing & BYTE_MASK) - 3] + ONE;
        } else {
            angle = D_801C8424[type & BYTE_MASK];
        }
        FIELD(s32, D_80147CC4, n * 0x10) = ((s16)angle - (g_Task->unk_6C & ANGLE_MASK)) / (g_Task->unk_0A * 4);
        return;
    }

    shadow                           = D_80147CB8 + n * 0x10;
    *(s32*)(shadow + 0xC)            = 0;
    *(s32*)(shadow + 0x8)            = 0;
    FIELD(s32, D_80147CBC, n * 0x10) = 0;
    FIELD(s32, work, 0x6Cu)          = D_801C8424[type & BYTE_MASK];
}
#else
INCLUDE_ASM(func_801A3080);
#endif
