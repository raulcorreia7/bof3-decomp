#include "area049_14.h"

extern s32 D_80145EC4;
extern s32 D_80145EC8;
extern u8  D_801F5C08[];

MATCH s32 func_801F2D00(u8 member) {
    s32 i = 0;
    s32 j = 0;
    s32 x = *(s32*)((u8*)&D_80145EC4 + member * 0x140);
    s32 y = *(s32*)((u8*)&D_80145EC8 + member * 0x140);
    while (i < 7) {
        if (x < ((s32)D_801F5C08[j + 0] << 16))
            goto next;
        if (x > ((s32)D_801F5C08[j + 2] << 16))
            goto next;
        if (y < ((s32)D_801F5C08[j + 1] << 16))
            goto next;
        if (y <= ((s32)D_801F5C08[j + 3] << 16))
            return i & 0xFF;
    next:
        i++;
        j += 6;
    }
    return 0xFF;
}
