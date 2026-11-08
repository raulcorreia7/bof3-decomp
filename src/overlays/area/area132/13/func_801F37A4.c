#include "area132_13.h"

MATCH void func_801F37A4(s32 arg0) {
    Actor* spad;
    u8*    ptr = (u8*)arg0;

    spad           = g_Task;
    ((s32*)ptr)[1] = spad->pos.x.fixed;
    ((s32*)ptr)[2] = spad->pos.y.fixed;
    ((s32*)ptr)[3] = ((s32*)spad)[0x3C / 4];
    ptr[0]         = 1;
    *(u16*)(ptr + 0x14) = 0x80;
    ptr[3]         = 0x40;
    ptr[0x16]      = 7;
    ptr[1]         = 0;
    ptr[2]         = 0x20;
}
