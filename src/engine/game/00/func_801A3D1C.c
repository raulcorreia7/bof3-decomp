#include "game_00.h"

MATCH void func_801A3D1C(void* unused) {
    Actor* work;
    s32    slot;
    s32    index;
    s8     n;
    s8     old_a;
    s8     old_b;

    if (g_Task->unk_06 == 0x0A) {
        slot = (s32)(-(((s32)g_CurrentActor - (s32)D_80147A58) * 0xD79435E5)) >> 3;
        n    = slot;
        if (n < 0) {
            n = 4;
        }
        index = n * 0x10;
        old_a = D_80147CB9[index];
        if (old_a != 0) {
            D_80147CB9[index] = old_a - 1;
            work              = g_Task;
            work->unk_64 += *(s32*)((u8*)D_80147CBC + index);
            work->unk_68 += *(s32*)((u8*)D_80147CC0 + index);
        }
        old_b = D_80147CBA[index];
        if (old_b != 0) {
            D_80147CBA[index] = old_b - 1;
            work              = g_Task;
            work->unk_6C += *(s32*)((u8*)D_80147CC4 + index);
        }
    }
}
