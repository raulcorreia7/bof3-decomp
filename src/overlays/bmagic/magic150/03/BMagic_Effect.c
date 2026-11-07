#include "magic150_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC20);

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EED60(void) {
    u8 timer;

    func_801EF6F8();
    func_801EF8EC();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EEDCC(void) {
    if (func_801EF8EC() == 0) {
        g_Task->unk_09      = 4;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

INCLUDE_ASM(func_801EEE24);

MATCH void func_801EEEC4(void) {
    u8 count;

    D_801EFAAC = ((g_FrameCount & 1) * 0x10) + 0x100;
    D_801EFAB0 -= 0x200;
    func_801EF254();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & 0xFF)) {
        g_Task->unk_09 = 4;
        g_Task->header.mode += 1;
        func_800A9820(g_BattleTargetSelector);
        SND_PlayCue(0x102U);
    }
}

/* blocker: D_801EFAAC and D_801EFAAE are one base-register pair in retail (a0 +0, +2); first diff: lui v0 against addiu a0 at 0x801EEF84. */
INCLUDE_ASM(func_801EEF80);

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF040);

MATCH void func_801EF254(void) {
    GFX_AddDrawMode(GetTPage(0, 1, 0x2C0, 0x100) & 0xFFFF);
    func_801AFE18();
    func_801EF040();
    func_801EF4E0();
}

/* blocker: the argument is a record with s32 at 0x00 and DVECTOR cells at 0x10, 0x14 and 0x18 passed to Area_ProjectPoint; needs: type (no record type in this image). */
INCLUDE_ASM(func_801EF2C0);

INCLUDE_ASM(func_801EF324);

INCLUDE_ASM(func_801EF4E0);

MATCH void func_801EF6B0(void) {
    u8   i;
    u16* work;

    D_801EFAF4 = D_801EFAB4;
    i          = 0;
    do {
        work = (u16*)D_801EFAF4;
        i++;
        *work = 0;
        work += 4;
        D_801EFAF4 = (u8*)work;
    } while (i < 8);
}

INCLUDE_ASM(func_801EF6F8);

INCLUDE_ASM(func_801EF790);

INCLUDE_ASM(func_801EF8EC);
