#include "area144_13.h"

#ifdef NON_MATCHING
/* Seeds the six area work rows the light path walks, then averages the corner
 * vectors of the eight-point star into its six midpoints. */
NON_MATCHING void func_801F2E18(void) {
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u8, 16);
    /* FAKE: the held constants keep their loads ahead of the row base; plain
     * literals schedule the base first. */
    u8  one;
    u8  shade;
    u8  three;
    u8* entry;
    s32 i;

    i = 0;
    /* FAKE: the held constants keep their loads ahead of the entry base. */
    FAKE_HOLD(one, 1);
    FAKE_HOLD(shade, 0xF0);
    FAKE_HOLD(three, 3);
    for (; (u16)i < 6; i++) {
        entry    = (u8*)(AREA_WORK + 0x14) + i * 0x1C;
        entry[4] = one;
        entry[5] = (u16)i * 15;
        entry[3] = 0;
        entry[0] = shade;
        entry[1] = shade;
        entry[2] = shade;
        if ((i & 1) == 0) {
            entry[7] = three;
        } else {
            entry[7] = one;
        }
    }

    *(u32*)(AREA_WORK + 0x00) = AREA_WORK + 0xA8;
    *(u32*)(AREA_WORK + 0x04) = AREA_WORK + 0xAC;
    *(u32*)(AREA_WORK + 0x08) = AREA_WORK + 0xB8;
    *(u32*)(AREA_WORK + 0x0C) = AREA_WORK + 0xBC;
    *(u32*)(AREA_WORK + 0x10) = AREA_WORK + 0xC8;
    *(u8*)(AREA_WORK + 0x1A)  = 1;
    func_801F376C(0, 5, 8);

    *(u32*)(AREA_WORK + 0x1C) = AREA_WORK + 0xA8;
    *(u32*)(AREA_WORK + 0x20) = AREA_WORK + 0xAC;
    *(u32*)(AREA_WORK + 0x24) = AREA_WORK + 0xB0;
    *(u32*)(AREA_WORK + 0x28) = AREA_WORK + 0xB4;
    *(u32*)(AREA_WORK + 0x2C) = AREA_WORK + 0xCC;
    *(u8*)(AREA_WORK + 0x36)  = 1;
    func_801F376C(0, 3, 9);

    *(u32*)(AREA_WORK + 0x48) = AREA_WORK + 0xD0;
    *(u32*)(AREA_WORK + 0x38) = AREA_WORK + 0xB0;
    *(u32*)(AREA_WORK + 0x3C) = AREA_WORK + 0xA8;
    *(u32*)(AREA_WORK + 0x40) = AREA_WORK + 0xC0;
    *(u32*)(AREA_WORK + 0x44) = AREA_WORK + 0xB8;
    *(u8*)(AREA_WORK + 0x52)  = 7;
    func_801F376C(2, 4, 0xA);

    *(u32*)(AREA_WORK + 0x54) = AREA_WORK + 0xB0;
    *(u32*)(AREA_WORK + 0x58) = AREA_WORK + 0xB4;
    *(u32*)(AREA_WORK + 0x5C) = AREA_WORK + 0xC0;
    *(u32*)(AREA_WORK + 0x60) = AREA_WORK + 0xC4;
    *(u32*)(AREA_WORK + 0x64) = AREA_WORK + 0xD4;
    func_801F376C(2, 7, 0xB);

    *(u8*)(AREA_WORK + 0x6E)  = 5;
    *(u32*)(AREA_WORK + 0x70) = AREA_WORK + 0xB8;
    *(u32*)(AREA_WORK + 0x74) = AREA_WORK + 0xBC;
    *(u32*)(AREA_WORK + 0x78) = AREA_WORK + 0xC0;
    *(u32*)(AREA_WORK + 0x7C) = AREA_WORK + 0xC4;
    *(u32*)(AREA_WORK + 0x80) = AREA_WORK + 0xD8;
    *(u8*)(AREA_WORK + 0x8A)  = 5;
    func_801F376C(4, 7, 0xC);

    *(u32*)(AREA_WORK + 0x8C) = AREA_WORK + 0xB4;
    *(u32*)(AREA_WORK + 0x90) = AREA_WORK + 0xAC;
    *(u32*)(AREA_WORK + 0x94) = AREA_WORK + 0xC4;
    *(u32*)(AREA_WORK + 0x98) = AREA_WORK + 0xBC;
    func_801F376C(3, 5, 0xD);
    *(u8*)(AREA_WORK + 0xA6)  = 3;
    *(u32*)(AREA_WORK + 0x9C) = AREA_WORK + 0xDC;
}
#else
INCLUDE_ASM(func_801F2E18);
#endif
