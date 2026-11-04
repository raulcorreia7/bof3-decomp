#include "sce15ef3_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D0C0C(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801D27C0[entity[1]]();
}

MATCH void func_801D0C48(void) {
    u8* work;

    work                   = (u8*)g_SpadWork;
    FIELD(s32, work, 0x34) = D_80145EC4;
    FIELD(s32, work, 0x38) = D_80145EC8;
    FIELD(s32, work, 0x3C) = D_80145ECC;
    func_801D16DC();
    func_801D19A0();
    work    = (u8*)g_SpadWork;
    work[9] = 0x78;
    work    = (u8*)g_SpadWork;
    work[1]++;
}

INCLUDE_ASM(func_801D0CC4);

MATCH void func_801D0D18(void) {
    Actor_Clear();
}

MATCH void func_801D0D38(void) {
    SYS_DISPATCH_TASK(D_801D27CC, 1, g_SpadWork);
}

MATCH void func_801D0D7C(void) {
    u8* work;

    work    = (u8*)g_SpadWork;
    work[9] = 8;
    work    = (u8*)g_SpadWork;
    work[1]++;
}

INCLUDE_ASM(func_801D0DAC);

INCLUDE_ASM(func_801D0E38);

MATCH void func_801D0EAC(void) {
    SYS_DISPATCH_TASK(D_801D27D8, 1, g_SpadWork);
}

INCLUDE_ASM(func_801D0EF0);

INCLUDE_ASM(func_801D0F94);

MATCH void func_801D1008(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_801D1028(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_801D1048(void) {
    Actor_Clear();
}

MATCH void func_801D1068(void) {
    SYS_DISPATCH_TASK(D_801D27EC, 1, g_SpadWork);
}

INCLUDE_ASM(func_801D10AC);

INCLUDE_ASM(func_801D11C8);

INCLUDE_ASM(func_801D1250);

INCLUDE_ASM(func_801D12E0);

INCLUDE_ASM(func_801D1370);

MATCH void func_801D13DC(void) {
    SYS_DISPATCH_TASK(D_801D2800, 1, g_SpadWork);
}

MATCH void func_801D1420(void) {
    g_SpadWork->unk_09 = 0;
    g_SpadWork->unk_06 = 0x10;
    g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
}

INCLUDE_ASM(func_801D1460);

MATCH void func_801D14DC(void) {
    g_SpadWork->unk_09 -= 0x10;
    if (g_AreaDrawFlags != 0) {
        func_801D23AC(g_SpadWork->unk_09);
    }
    if (g_SpadWork->unk_09 == 0) {
        if (g_AreaDrawFlags == 0) {
            Actor_Clear();
        } else {
            g_SpadWork->unk_01--;
        }
    }
}

MATCH void func_801D1588(void) {
    SYS_DISPATCH_TASK(D_801D280C, 1, g_SpadWork);
}

MATCH void func_801D15CC(void) {
    Actor* work;

    work         = g_SpadWork;
    work->unk_2E = 300;
    work->unk_09 = 0;
    Scene_ClearSlots();
    g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
}

INCLUDE_ASM(func_801D1614);

MATCH void func_801D16BC(void) {
    Actor_Clear();
}

MATCH void func_801D16DC(void) {
    s32   index;
    s8*   row;
    void* tail;

    row   = (s8*)AREA_WORK_WINDOW;
    index = 0;
    tail  = (void*)(AREA_WORK_WINDOW + 2);
    do {
        *row                     = 0;
        *(s8*)((u8*)(tail) + -1) = 0;
        *(s8*)(tail)             = 0;
        tail += 0x18;
        index += 1;
        row += 0x18;
    } while ((u32)(index & HALF_MASK) < 0x100U);
}

MATCH u8* func_801D171C(void) {
    u8* p;
    u16 i;

    p = MEM_PTR(u8, 0x800E4800);
    for (i = 0; i < 256; i++) {
        if (p[0] == 0) {
            return p;
        }
        p += 0x18;
    }
    return NULL;
}

INCLUDE_ASM(func_801D1758);

/* Steps the 256 slots at 0x800E4800 (stride 0x18): speed += 0x20000, position += speed, flip ^= 1, func_801D1758(slot),
 * --life frees at zero, returns 1 when a slot was live. Every form of the speed update hoists the 0x20000 into s4 (frame
 * 0x4C, first differing instruction +0x10: sw ra,64(sp) against 68); retail keeps the lui inside the loop. */
INCLUDE_ASM(func_801D18CC);

/* Fills the eight 0x14-byte slots at 0x800E6000 (active = 1, two rand bytes, x and y from the s8 pair table at D_801D27B0
 * shifted 16, z = Area_SampleHeight(x, y) << 16). The loop body matches, but retail's frame is 0x30 against 0x20: it
 * reserves 16 bytes of locals no form of the body produces (first differing instruction +0x0: addiu sp,sp,-48). */
INCLUDE_ASM(func_801D19A0);

INCLUDE_ASM(func_801D1A60);

INCLUDE_ASM(func_801D1BAC);

INCLUDE_ASM(func_801D1D20);

INCLUDE_ASM(func_801D1FF8);

INCLUDE_ASM(func_801D230C);

INCLUDE_ASM(func_801D23AC);

INCLUDE_ASM(func_801D2424);

#include "overlays/scenario/Scene_ClearSlots.h"

#include "overlays/scenario/Scene_ClaimSlot.h"

INCLUDE_ASM(func_801D2634);
