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
    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EEDCC(void) {
    if (func_801EF8EC() == 0) {
        g_SpadWork->word_08.byte.unk_09 = 4;
        g_SpadWork->step_01             = g_SpadWork->step_01 + 1;
    }
}

INCLUDE_ASM(func_801EEE24);

MATCH void func_801EEEC4(void) {
    u8 temp_v0;

    D_801EFAAC = ((g_FrameCount & 1) * 0x10) + 0x100;
    D_801EFAB0 -= 0x200;
    func_801EF254();
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->word_08.byte.unk_09 = 4;
        g_SpadWork->step_01 += 1;
        func_800A9820(g_BattleTargetSelector);
        SND_PlayCue(0x102U);
    }
}

INCLUDE_ASM(func_801EEF80);

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF040);

MATCH void func_801EF254(void) {
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 0x2C0, 0x100) & 0xFFFF, NULL);
    GFX_AddPrim(1U, 0xCU);
    func_801AFE18();
    func_801EF040();
    func_801EF4E0();
}

INCLUDE_ASM(func_801EF2C0);

INCLUDE_ASM(func_801EF324);

INCLUDE_ASM(func_801EF4E0);

MATCH void func_801EF6B0(void) {
    u8  i;
    u8* work;

    D_801EFAF4 = D_801EFAB4;
    i          = 0;
    do {
        work = D_801EFAF4;
        i++;
        *(u16*)work = 0;
        work += 8;
        D_801EFAF4 = work;
    } while (i < 8);
}

INCLUDE_ASM(func_801EF6F8);

INCLUDE_ASM(func_801EF790);

INCLUDE_ASM(func_801EF8EC);
