#include "game_00.h"

MATCH void func_8019D9C0(void) {
    Actor* work;
    s32*   dst;
    s32    count;
    s32*   dst2;

    dst        = MEM_PTR(s32, 0x800E4D44u);
    count      = 0;
    dst2       = MEM_PTR(s32, 0x800E4D5Cu);
    D_800E4D40 = 0x40;
    D_800E4D42 = 0;
    /* NOTE: a goto loop; gcc 2.7.2 strength-reduces a do/while here (+20 bytes). */
loop:
    work        = g_Task;
    *dst        = work->pos.x.fixed;
    *(dst2 - 5) = work->pos.y.fixed;
    /* Third coord word follows y.fixed with no named field. */
    *(dst2 - 4) = ((s32*)&work->pos.x.fixed)[2];
    count += 1;
    *(dst2 - 2) = (rand() & 0xFF) - 0x80;
    *(dst2 - 1) = (rand() & 0xFF) - 0x80;
    *dst2       = rand() & 0x7F;
    VectorNormal((VECTOR*)(dst + 4), (VECTOR*)(dst + 4));
    *dst2 = *dst2 << 9;
    dst += 8;
    dst2 += 8;
    if (((count & 0xFF)) < 8U) {
        goto loop;
    }
}
