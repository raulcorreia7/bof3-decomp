#include "commu02_08.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801D1394);

MATCH void func_801D143C(void) {
    s8 value;

    value      = (u8)D_801DB0C4 + 1;
    D_801DB0C4 = value;
    func_801D3184(0x6E - ((value & 0xFF) * 0x28), 0x48);
    func_801D32A0(0x6E - ((u8)D_801DB0C4 * 0x28), 0x74, 1);
    if ((u8)D_801DB0C4 == 4) {
        func_801D2E10();
    }
}

MATCH void func_801D14D0(void) {
    SYS_DISPATCH_BYTE(D_801DAC20, D_801F294E);
}

INCLUDE_ASM(func_801D150C);

INCLUDE_ASM(func_801D15A4);

INCLUDE_ASM(func_801D1774);

INCLUDE_ASM(func_801D184C);

INCLUDE_ASM(func_801D1938);

INCLUDE_ASM(func_801D1A50);

INCLUDE_ASM(func_801D1D68);

INCLUDE_ASM(func_801D1E98);

MATCH void func_801D1FE4(void) {
    s32 temp_a0;
    s8 temp_v0;

    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    temp_a0 = (D_801DB0B4 + 1) & 0xFF;
    func_801D2794(temp_a0, temp_a0, D_801DB0B4);
    temp_v0 = (u8) D_801DB0C4 - 1;
    D_801DB0C4 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        SND_PlayCue(0x102U);
        D_801F294D += 1;
    }
}

INCLUDE_ASM(func_801D2078);

INCLUDE_ASM(func_801D21FC);

INCLUDE_ASM(func_801D22A4);

INCLUDE_ASM(func_801D2320);

MATCH void func_801D24A8(void) {
    s8 temp_v1;

    if (g_GameStateIndex != 2) {
        if (D_801F294E == 0) {
            func_801D3184(0x26, 0x10);
            func_801D32A0(0xA8, 0x10, 0);
            SND_PlayCue(0x102U);
            D_801DB0C4 = 0;
            D_801F294E += 1;
            return;
        }
        temp_v1 = (u8) D_801DB0C4 + 1;
        D_801DB0C4 = temp_v1;
        func_801D3184(0x26, 0x10 - ((temp_v1 & 0xFF) * 0x14));
        func_801D32A0(0xA8, 0x10 - ((u8) D_801DB0C4 * 0x14), 0);
        if ((u8) D_801DB0C4 == 4) {
            D_801F294C = 2;
            D_801F294D = 0;
        }
    } else {
        func_801D3184(0x26, 0x10);
        func_801D32A0(0xA8, 0x10, 0);
    }
}

INCLUDE_ASM(func_801D25CC);

INCLUDE_ASM(func_801D269C);

MATCH s32 func_801D2750(s32 arg0) {
    s32 roll;

    do {
        roll = rand() & 0xF;
    } while (roll == 0 || roll >= ((arg0 & 0xFF) + 1));
    return roll;
}

INCLUDE_ASM(func_801D2794);

INCLUDE_ASM(func_801D2870);

INCLUDE_ASM(func_801D2908);

INCLUDE_ASM(func_801D2AC4);

INCLUDE_ASM(func_801D2CF8);

MATCH void func_801D2E10(void) {
    SND_PlayCue(262);
    Message_StartAreaMessage(114);
    g_GameStateIndex = 2;
    D_801F294D       = 0;
    D_801F294C++;
}

INCLUDE_ASM(func_801D2E60);

INCLUDE_ASM(func_801D2EDC);

INCLUDE_ASM(func_801D2FA4);

INCLUDE_ASM(func_801D3184);

INCLUDE_ASM(func_801D32A0);

MATCH void func_801D3568(void) {
    SYS_DISPATCH_BYTE(D_801DACB8, D_801F294C);
}

MATCH void func_801D35A4(void) {
    SYS_DISPATCH_BYTE(D_801DACC4, D_801F294D);
}

INCLUDE_ASM(func_801D35E0);

MATCH void func_801D364C(void) {
    if (EMI_LoaderIsReady() != 0) {
        SND_PlayBgm(0x94, 0x64, 8);
        Message_StartAreaMessage(0x7F);
        g_GameStateIndex = 2;
        D_801F294D += 1;
    }
}

MATCH void func_801D36A8(void) {
    if (g_GameStateIndex != 2) {
        SND_PlayCue(0x102U);
        D_801DB0C4 = 4;
        D_801DB07C = 0;
        D_801F294D += 1;
    }
}

INCLUDE_ASM(func_801D3700);

MATCH void func_801D37EC(void) {
    SYS_DISPATCH_BYTE(D_801DACD4, D_801F294D);
}

MATCH void func_801D3828(void) {
    SYS_DISPATCH_BYTE(D_801DACF8, D_801F294E);
}

INCLUDE_ASM(func_801D3864);

INCLUDE_ASM(func_801D39A4);

MATCH void func_801D3B04(void) {
    Message_StartAreaMessage(128);
    g_GameStateIndex = 2;
    D_801F294D++;
    func_801D4AE0(16, 24, 0);
    func_801D4F88(104, 64, 0);
    func_801D4EA4(104, 120, D_801DB0B4, 0);
    func_801D3184(204, 16);
    func_801D32A0(204, 60, 0);
}

MATCH void func_801D3B98(void) {
    if (g_GameStateIndex != 2) {
        D_801DB0B8 = 0;
        D_801F294D += 1;
    }
    func_801D4AE0(0x10, 0x18, 0);
    func_801D4F88(0x68, 0x40, 0);
    func_801D4EA4(0x68, 0x78, D_801DB0B4, 0);
    func_801D3184(0xCC, 0x10);
    func_801D32A0(0xCC, 0x3C, 0);
}

INCLUDE_ASM(func_801D3C30);

INCLUDE_ASM(func_801D3E44);

INCLUDE_ASM(func_801D4158);

INCLUDE_ASM(func_801D42B4);

INCLUDE_ASM(func_801D437C);

INCLUDE_ASM(func_801D448C);

INCLUDE_ASM(func_801D4840);

INCLUDE_ASM(func_801D4910);

INCLUDE_ASM(func_801D4AE0);

INCLUDE_ASM(func_801D4EA4);

INCLUDE_ASM(func_801D4F88);

MATCH void func_801D5034(void) {
    SYS_DISPATCH_BYTE(D_801DAD68, D_801F294C);
}

MATCH void func_801D5070(void) {
    SYS_DISPATCH_BYTE(D_801DAD74, D_801F294D);
}

MATCH void func_801D50AC(void) {
    UI_SetMode(0);
    D_801F294D += 1;
}

INCLUDE_ASM(func_801D50E4);

MATCH void func_801D5194(void) {
    SYS_DISPATCH_BYTE(D_801DAD7C, D_801F294D);
}

INCLUDE_ASM(func_801D51D0);

INCLUDE_ASM(func_801D5788);

INCLUDE_ASM(func_801D5924);

MATCH void func_801D5978(void) {
    s32 temp_v0;

    if (g_UiWindowEffectBusy == 0) {
        temp_v0 = g_SndBgmId * 4;
        SND_StopSequence((s32) *(g_SelectionCues + temp_v0), (s16) *(D_80181EBB + temp_v0));
        SND_RequestBgm((s32) D_801DB0CC);
loop_2:
        if (EMI_LoaderIsReady() == 0) {
            CallbackWait(1U);
            goto loop_2;
        }
        SND_PlayBgm((s32) D_801DB0CC, 0x64, 8);
        g_AreaDrawFlags = 0x1F;
        UI_SetMode(1U);
        D_801F294D += 1;
        return;
    }
    func_801D5B2C();
}

MATCH void func_801D5A48(void) {
    if (g_UiWindowEffectBusy == 0) {
        Message_StartAreaMessage(0xE2);
        g_GameStateIndex = 2;
        D_801F294D = 0;
        D_801F294C += 1;
    }
}

#include "overlays/commu/Commu_AdvanceStep.h"

INCLUDE_ASM(func_801D5AD0);

INCLUDE_ASM(func_801D5B2C);

MATCH void func_801D5D5C(void) {
    SYS_DISPATCH_BYTE(D_801DADEC, D_801F294C);
}

INCLUDE_ASM(func_801D5D98);

MATCH void func_801D5DF4(void) {
    SYS_DISPATCH_BYTE(D_801DAE00, D_801F294D);
}

MATCH void func_801D5E30(void) {
    if (g_GameStateIndex != 2) {
        SND_PlayCue(0x102);
        D_801DB0C4 = 4;
        D_801DB0B4 = 0;
        D_801DB0C8 = 0xF0;
        D_801F294D += 1;
    }
}

INCLUDE_ASM(func_801D5E94);

INCLUDE_ASM(func_801D5F7C);

INCLUDE_ASM(func_801D6124);

MATCH void func_801D62C8(void) {
    s8 temp_v1;

    temp_v1 = (u8) D_801DB0C4 + 1;
    D_801DB0C4 = temp_v1;
    Menu_DrawHeaderBar(0x14, (0x10 - ((temp_v1 & 0xFF) * 8)) & 0xFFF8, 0x118, 0x13, (s32) D_80144952);
    func_801D8058(0x4A, ((u8) D_801DB0C4 * 0x28) + 0x64);
    func_801D830C(0x44, 0x32, func_801D7EA0(D_801DB0B4) & 0xFF, 0);
    if ((u8) D_801DB0C4 == 4) {
        D_801DB0C4 = 5;
        D_801F294D = 7;
    }
}

MATCH void func_801D6390(void) {
    u8 value;

    if (g_GameStateIndex != 2) {
        if (D_801F2944 == 0) {
            value = 6;
        } else {
            D_801DB0C4 = 5;
            value      = 7;
        }
        D_801F294D = value;
    }
    func_801D830C(0x44, 0x32, func_801D7EA0(D_801DB0B4) & 0xFF, 0);
}

MATCH void func_801D640C(void) {
    SYS_DISPATCH_BYTE(D_801DAE24, D_801F294E);
}

INCLUDE_ASM(func_801D6448);

MATCH void func_801D64E0(void) {
    if (g_GameStateIndex != 2) {
        if (D_801F2945 != 0) {
            SND_PlayCue(0x102U);
            D_801DB0C4 = 0;
            D_801F294E += 1;
        } else {
            D_801F294E = 0;
        }
    }
    func_801D830C(0x44, 0x32, func_801D7EA0(D_801DB0B4) & 0xFF, 0);
}

MATCH void func_801D6574(void) {
    D_801DB0C4 = (u8)D_801DB0C4 + 1;
    func_801D830C(0x44 - ((u8)D_801DB0C4 * 0x1E), 0x32, func_801D7EA0(D_801DB0B4) & 0xFF, 0);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA8E8();
    }
}

MATCH void func_801D65F8(void) {
    SYS_DISPATCH_BYTE(D_801DAE30, D_801F294E);
}

INCLUDE_ASM(func_801D6634);

MATCH void func_801D67F0(void) {
    func_801D830C(0x44, 0x32, func_801D7EA0(D_801DB0B4) & 0xFF, 1);
    func_801AE214((D_801DB0D0 * 8) + 0x4A, 0x42, 8, 0);
    func_801D97C8(D_801DAAA8, 0xB0, 0x2B);
    func_801D9B80(0x12, 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, 0x67, D_801DB0D4, (s32) D_801DB0D8);
    D_801DB0DC = func_801DA114();
}

INCLUDE_ASM(func_801D68AC);

MATCH void func_801D6AC8(void) {
    func_801D830C(0x44, 0x32, func_801D7EA0(D_801DB0B4) & 0xFF, 1);
    if (g_GameStateIndex != 2) {
        if (D_801F2945 == 0) {
            D_801DB0C4 = 0;
            D_801F294E += 1;
            return;
        }
        D_801DB0C4 = 4;
        D_801F294E = 0;
    }
}

MATCH void func_801D6B60(void) {
    D_801DB0C4 = (u8)D_801DB0C4 + 1;
    func_801D830C(0x44 - ((u8)D_801DB0C4 * 0x1E), 0x32, func_801D7EA0(D_801DB0B4) & 0xFF, 1);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA8E8();
    }
}

MATCH void func_801D6BE4(void) {
    s8 temp_v1;

    temp_v1 = (u8) D_801DB0C4 + 1;
    D_801DB0C4 = temp_v1;
    Menu_DrawHeaderBar(0x14, (0x10 - ((temp_v1 & 0xFF) * 8)) & 0xFFF8, 0x118, 0x13, (s32) D_80144952);
    func_801D830C(0x20 - ((u8) D_801DB0C4 * 0x1E), 0x32, func_801D7EA0(D_801DB0B4) & 0xFF, 0);
    func_801D8058(0x4A, 0x64 - ((u8) D_801DB0C4 * 0x1E));
    if ((u8) D_801DB0C4 == 4) {
        Message_StartAreaMessage(0xF7);
        g_GameStateIndex = 2;
        D_801F294C = 4;
        D_801F294D = 0;
    }
}

MATCH void func_801D6CDC(void) {
    SYS_DISPATCH_BYTE(D_801DAE44, D_801F294D);
}

INCLUDE_ASM(func_801D6D18);

INCLUDE_ASM(func_801D6E70);

INCLUDE_ASM(func_801D708C);

INCLUDE_ASM(func_801D7234);

MATCH void func_801D73F8(void) {
    u8 value;

    if (g_GameStateIndex != 2) {
        if (D_801F2944 == 0) {
            value = 6;
        } else {
            D_801DB0C4 = 4;
            value      = 7;
        }
        D_801F294D = value;
    }
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & 0xFF, 0);
}

MATCH void func_801D7474(void) {
    SYS_DISPATCH_BYTE(D_801DAE68, D_801F294E);
}

INCLUDE_ASM(func_801D74B0);

MATCH void func_801D7548(void) {
    if (g_GameStateIndex != 2) {
        if (D_801F2945 != 0) {
            SND_PlayCue(0x102U);
            D_801DB0C4 = 0;
            D_801F294E += 1;
        } else {
            D_801F294E = 0;
        }
    }
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & 0xFF, 0);
}

MATCH void func_801D75DC(void) {
    D_801DB0C4 = (u8)D_801DB0C4 + 1;
    func_801D90D8(0x20 - ((u8)D_801DB0C4 * 0x28), 0x2B, func_801D92F4(D_801DB0B4) & 0xFF, 0);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA7A4();
    }
}

MATCH void func_801D7660(void) {
    SYS_DISPATCH_BYTE(D_801DAE74, D_801F294E);
}

INCLUDE_ASM(func_801D769C);

MATCH void func_801D7878(void) {
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & 0xFF, 1);
    func_801AE214((D_801DB0D0 * 8) + 0x5B, 0x50, 8, 0);
    func_801D97C8(D_801DAAA8, 0xB0, 0x2B);
    func_801D9B80(0x12, 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, 0x67, D_801DB0D4, (s32) D_801DB0D8);
    D_801DB0DC = func_801DA114();
}

INCLUDE_ASM(func_801D7934);

MATCH void func_801D7B50(void) {
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & 0xFF, 1);
    if (g_GameStateIndex != 2) {
        if (D_801F2945 == 0) {
            D_801DB0C4 = 0;
            D_801F294E += 1;
            return;
        }
        D_801DB0C4 = 4;
        D_801F294E = 0;
    }
}

MATCH void func_801D7BE8(void) {
    D_801DB0C4 = (u8)D_801DB0C4 + 1;
    func_801D90D8(0x20 - ((u8)D_801DB0C4 * 0x1E), 0x2B, func_801D92F4(D_801DB0B4) & 0xFF, 1);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA7A4();
    }
}

INCLUDE_ASM(func_801D7C6C);

INCLUDE_ASM(func_801D7DD4);

/* func_801D7E30: the same body as the second copy in this image */
#define Commu_AdvanceStep func_801D7E30
#include "overlays/commu/Commu_AdvanceStep.h"
#undef Commu_AdvanceStep

#include "overlays/commu/Fairy_VillageCountFairies.h"

INCLUDE_ASM(func_801D7EA0);

INCLUDE_ASM(func_801D7EF0);

INCLUDE_ASM(func_801D8058);

INCLUDE_ASM(func_801D812C);

INCLUDE_ASM(func_801D81A4);

INCLUDE_ASM(func_801D830C);

INCLUDE_ASM(func_801D851C);

INCLUDE_ASM(func_801D875C);

INCLUDE_ASM(func_801D88A4);

INCLUDE_ASM(func_801D8968);

INCLUDE_ASM(Menu_DrawHeaderBar);

#include "shared/Menu_DrawPortrait.h"

INCLUDE_ASM(func_801D90D8);

INCLUDE_ASM(func_801D9210);

INCLUDE_ASM(func_801D92B0);

INCLUDE_ASM(func_801D92F4);

INCLUDE_ASM(func_801D9348);

INCLUDE_ASM(func_801D94D0);

INCLUDE_ASM(func_801D97C8);

MATCH void Menu_DrawIcon(s16 x, s16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

INCLUDE_ASM(func_801D9B80);

INCLUDE_ASM(func_801DA114);

INCLUDE_ASM(func_801DA7A4);

INCLUDE_ASM(func_801DA8E8);
