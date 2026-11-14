#include "commu02_08.h"
#include "overlays/commu/Commu_CursorTriangle.h"
#include "common/util.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801D1394);

MATCH void func_801D143C(void) {
    s8 value;

    value      = D_801DB0C4 + 1;
    D_801DB0C4 = value;
    func_801D3184(0x6E - ((value & BYTE_MASK) * 0x28), 0x48);
    func_801D32A0(0x6E - ((u8)D_801DB0C4 * 0x28), 0x74, 1);
    if ((u8)D_801DB0C4 == 4) {
        func_801D2E10();
    }
}

MATCH void func_801D14D0(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event0Step1Sub3Funcs, D_801F294E);
}

MATCH void func_801D150C(void) {
    s32 i;
    s8* ptr;

    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        i   = 9;
        ptr = &D_801DB093;
        do {
            *ptr = 0;
            i -= 1;
            ptr -= 1;
        } while (i >= 0);
        func_801D2870();
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        D_801DB0C4 = 3;
        D_801DB0B4 = 0;
        D_801F294E += 1;
    }
}

INCLUDE_ASM(func_801D15A4);

INCLUDE_ASM(func_801D1774);

INCLUDE_ASM(func_801D184C);

MATCH void func_801D1938(void) {
    s8 count;
    u8 check;

    func_801D2794(9, 1, 0);
    count      = D_801DB0C4 - 1;
    D_801DB0C4 = count;
    func_801D2AC4(0x58, 0x44 - ((count & BYTE_MASK) * 0x1E), 0, 0);
    func_801D2AC4(0x88, 0x44 - ((u8)D_801DB0C4 * 0x1E), 1, 0);
    func_801D2AC4(0xB8, 0x44 - ((u8)D_801DB0C4 * 0x1E), 2, 0);
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    check = D_801DB0C4;
    if (check == 0) {
        D_801DB0B4 = 0;
        D_801DB0B8 = 0;
        D_801F294E = 0;
        D_801F294D += 1;
    }
}

INCLUDE_ASM(func_801D1A50);

INCLUDE_ASM(func_801D1D68);

INCLUDE_ASM(func_801D1E98);

MATCH void func_801D1FE4(void) {
    s32 index;
    s8  count;

    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    index = (D_801DB0B4 + 1) & BYTE_MASK;
    func_801D2794(index, index, D_801DB0B4);
    count      = D_801DB0C4 - 1;
    D_801DB0C4 = count;
    if (!(count & BYTE_MASK)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        D_801F294D += 1;
    }
}

INCLUDE_ASM(func_801D2078);

MATCH void func_801D21FC(void) {
    u8* state = &g_GameStateIndex;

    if (*state != 2) {
        if (D_801DB07C >= 0x2710) {
            Message_StartAreaMessage(0x79);
            *state = 2;
            D_801F294D += 1;
        } else {
            Message_StartAreaMessage(0x78);
            *state     = 2;
            D_801F294D = 3;
        }
    }
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
}

MATCH void func_801D22A4(void) {
    u8* state = &g_GameStateIndex;

    if (*state != 2) {
        Party_AddZenny(D_801DB07C, 0);
        Message_StartAreaMessage(0x75);
        D_801DB07C = 0;
        *state     = 2;
    }
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
}

INCLUDE_ASM(func_801D2320);

MATCH void func_801D24A8(void) {
    s8 step;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (D_801F294E == 0) {
            func_801D3184(0x26, 0x10);
            func_801D32A0(0xA8, 0x10, 0);
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
            D_801DB0C4 = 0;
            D_801F294E += 1;
            return;
        }
        step       = D_801DB0C4 + 1;
        D_801DB0C4 = step;
        func_801D3184(0x26, 0x10 - ((step & BYTE_MASK) * 0x14));
        func_801D32A0(0xA8, 0x10 - ((u8)D_801DB0C4 * 0x14), 0);
        if ((u8)D_801DB0C4 == 4) {
            D_801F294C = 2;
            D_801F294D = 0;
        }
    } else {
        func_801D3184(0x26, 0x10);
        func_801D32A0(0xA8, 0x10, 0);
    }
}

MATCH void func_801D25CC(void) {
    s32 bgm_offset;
    u8* step;

    if (D_801F294D == 0) {
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
            bgm_offset = g_SndBGMId * 4;
            SND_StopSequence(g_SelectionCues[bgm_offset], g_SelectionCues[bgm_offset + 1]);
            SND_RequestBGM(D_801DB0CC);
            D_801F294D += 1;
        }
    } else if (EMI_IsReady() != 0) {
        SND_PlayBGM(D_801DB0CC, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
        step  = &g_SceneEventStep;
        *step = *step + 1;
    }
}

INCLUDE_ASM(func_801D269C);

MATCH s32 func_801D2750(s32 limit) {
    s32 roll;

    do {
        roll = RANDOM_MASK(0xF);
    } while (roll == 0 || roll >= ((limit & BYTE_MASK) + 1));
    return roll;
}

INCLUDE_ASM(func_801D2794);

MATCH void func_801D2870(void) {
    s32 i;
    s32 j;
    s32 value;

    D_801DB080[0] = func_801D2750(9);
    for (i = 1; i < 9; i++) {
        do {
            value = func_801D2750(9);
            for (j = 0; j < i; j++) {
                if ((u8)value == D_801DB080[j]) {
                    break;
                }
            }
        } while (j != i);
        D_801DB080[i] = value;
    }
}

INCLUDE_ASM(func_801D2908);

INCLUDE_ASM(func_801D2AC4);

INCLUDE_ASM(func_801D2CF8);

MATCH void func_801D2E10(void) {
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    Message_StartAreaMessage(114);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    D_801F294D       = 0;
    D_801F294C++;
}

MATCH void func_801D2E60(s16 x, s16 y) {
    LINE_F2* primitive;

    primitive = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(primitive);
    primitive->x0 = x;
    primitive->x1 = x + 8;
    primitive->y0 = y;
    primitive->y1 = y;
    setRGB0(primitive, 0x80, 0x80, 0x80);
    GFX_AddPrim(1, sizeof(LINE_F2));
}

INCLUDE_ASM(func_801D2EDC);

INCLUDE_ASM(func_801D2FA4);

INCLUDE_ASM(func_801D3184);

INCLUDE_ASM(func_801D32A0);

MATCH void func_801D3568(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event1States, D_801F294C);
}

MATCH void func_801D35A4(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event1Step0Funcs, D_801F294D);
}

MATCH void func_801D35E0(void) {
    /* Plain pointers: const lifts the two reads above the D_801DB0CC store. */
    u8* cues;
    u8* sequences;

    D_801DB0CC = g_SndBGMId;
    cues       = g_SelectionCues + g_SndBGMId * 4;
    sequences  = g_SelectionSequences + g_SndBGMId * 4;
    SND_StopSequence(*cues, *sequences);
    SND_RequestBGM(BGM_COMMU02);
    D_801F294D += 1;
}

MATCH void func_801D364C(void) {
    if (EMI_IsReady() != 0) {
        SND_PlayBGM(BGM_COMMU02, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
        Message_StartAreaMessage(0x7F);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        D_801F294D += 1;
    }
}

MATCH void func_801D36A8(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        D_801DB0C4 = 4;
        D_801DB07C = 0;
        D_801F294D += 1;
    }
}

MATCH void func_801D3700(void) {
    s8 count;
    u8 check;

    count      = D_801DB0C4 - 1;
    D_801DB0C4 = count;
    func_801D4AE0(0x10 - ((count & BYTE_MASK) * 0x1E), 0x18, 0);
    func_801D3184(((u8)D_801DB0C4 * 0x1E) + 0xCC, 0x10);
    func_801D32A0(((u8)D_801DB0C4 * 0x1E) + 0xCC, 0x3C, 0);
    func_801D2CF8(0x68, 0x40 - ((u8)D_801DB0C4 * 0x1E), 0xFF);
    check = D_801DB0C4;
    if (check == 0) {
        D_801F294D = 0;
        D_801F294C += 1;
    }
}

MATCH void func_801D37EC(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event1Step1Funcs, D_801F294D);
}

MATCH void func_801D3828(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event1Step1Sub0Funcs, D_801F294E);
}

INCLUDE_ASM(func_801D3864);

MATCH void func_801D39A4(void) {
    u8 check;

    D_801DB0C4 = D_801DB0C4 - 1;
    func_801D4AE0(0x10, 0x18, 0);
    func_801D3184(0xCC, 0x10);
    func_801D32A0(0xCC, 0x3C, 0);
    func_801D2CF8(0xA8 - ((u8)D_801DB0C4 * 8), 0x78 - ((u8)D_801DB0C4 * 0xE), 1);
    func_801D2CF8(0x88 - ((u8)D_801DB0C4 * 8), 0x78 - ((u8)D_801DB0C4 * 0xE), 1);
    func_801D2CF8(0x68, 0x78 - ((u8)D_801DB0C4 * 0xE), 1);
    func_801D2CF8(0xA8 - ((u8)D_801DB0C4 * 8), 0x40, 0xFF);
    func_801D2CF8(0x88 - ((u8)D_801DB0C4 * 8), 0x40, 0xFF);
    func_801D2CF8(0x68, 0x40, 0xFF);
    check = D_801DB0C4;
    if (check == 0) {
        D_801F294E = 0;
        D_801F294D += 1;
    }
}

MATCH void func_801D3B04(void) {
    Message_StartAreaMessage(128);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    D_801F294D++;
    func_801D4AE0(16, 24, 0);
    func_801D4F88(104, 64, 0);
    func_801D4EA4(104, 120, D_801DB0B4, 0);
    func_801D3184(204, 16);
    func_801D32A0(204, 60, 0);
}

MATCH void func_801D3B98(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
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

MATCH void func_801D4840(void) {
    s32 bgm_offset;
    u8* step;

    if (D_801F294D == 0) {
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
            bgm_offset = g_SndBGMId * 4;
            SND_StopSequence(g_SelectionCues[bgm_offset], g_SelectionCues[bgm_offset + 1]);
            SND_RequestBGM(D_801DB0CC);
            D_801F294D += 1;
        }
    } else if (EMI_IsReady() != 0) {
        SND_PlayBGM(D_801DB0CC, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
        step  = &g_SceneEventStep;
        *step = *step + 1;
    }
}

INCLUDE_ASM(func_801D4910);

INCLUDE_ASM(func_801D4AE0);

INCLUDE_ASM(func_801D4EA4);

MATCH void func_801D4F88(s32 x, s32 y, s32 show_values) {
    s32 i;
    s32 draw_x;
    s32 draw_y;

    if ((u8)show_values) {
        i      = 0;
        draw_y = y << 16;
        draw_x = x;
        do {
            func_801D2CF8((s16)draw_x, draw_y >> 16, D_801DB080[i]);
            draw_x += 0x20;
            i++;
        } while (i < 3);
    } else {
        i      = 0;
        draw_y = y << 16;
        draw_x = x;
        do {
            func_801D2CF8((s16)draw_x, draw_y >> 16, 0xFF);
            draw_x += 0x20;
            i++;
        } while (i < 3);
    }
}

MATCH void func_801D5034(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event2States, D_801F294C);
}

MATCH void func_801D5070(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event2Step0Funcs, D_801F294D);
}

MATCH void func_801D50AC(void) {
    UI_SetMode(UI_MODE_FADE_OUT);
    D_801F294D += 1;
}

INCLUDE_ASM(func_801D50E4);

MATCH void func_801D5194(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event2Step1Funcs, D_801F294D);
}

INCLUDE_ASM(func_801D51D0);

INCLUDE_ASM(func_801D5788);

MATCH void func_801D5924(void) {
    func_801D5B2C();
    if (g_InputPressed != 0) {
        UI_SetMode(0U);
        D_801F294D += 1;
    }
}

MATCH void func_801D5978(void) {
    s32 offset;

    if (g_UiWindowEffectBusy == 0) {
        offset = g_SndBGMId * 4;
        SND_StopSequence(g_SelectionCues[offset], g_SelectionCues[offset + 1]);
        SND_RequestBGM(D_801DB0CC);
    loop_2:
        if (EMI_IsReady() == 0) {
            SYS_ThreadWait(1U);
            goto loop_2;
        }
        SND_PlayBGM(D_801DB0CC, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
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
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        D_801F294D       = 0;
        D_801F294C += 1;
    }
}

#include "overlays/commu/Fairy_EndCommuScene.h"

MATCH s32 func_801D5AD0(s32 limit) {
    s32 roll;

    roll = RANDOM_MASK(0x7F);
    FAKE_ORDER_LOCK_BEGIN
    loop_1:
        if ((roll & BYTE_MASK) >= (u32)(limit & BYTE_MASK)) {
            roll -= RANDOM_MASK(0xF);
            goto loop_1;
        }
    FAKE_ORDER_LOCK_END;
    return roll & BYTE_MASK;
}

MATCH void func_801D5B2C(void) {
    u8* src;
    u8  i;
    s32 j;

    g_UiFormatBuffer[0] = 0x2A;
    i                   = 1;
    src                 = (u8*)AREA_MESSAGE_TABLE + MEM(u16, (u32)AREA_MESSAGE_TABLE + (256 + D_801DB0AD) * 2);
    while (*src != STRING_END) {
        g_UiFormatBuffer[i] = *src;
        i++;
        if ((u8)(*src - STRING_SKIP) < 2) {
            src++;
            g_UiFormatBuffer[i] = *src;
            i++;
        }
        src++;
    }
    if (D_801DB0AE != 0xFF) {
        src = (u8*)AREA_MESSAGE_TABLE + MEM(u16, (u32)AREA_MESSAGE_TABLE + (256 + D_801DB0AE) * 2);
        while (*src != STRING_END) {
            g_UiFormatBuffer[i] = *src;
            i++;
            if ((u8)(*src - STRING_SKIP) < 2) {
                src++;
                g_UiFormatBuffer[i] = *src;
                i++;
            }
            src++;
        }
    }
    g_UiFormatBuffer[i] = 0x2B;
    i++;
    g_UiFormatBuffer[i] = STRING_SPACE;
    i++;
    for (j = 0; j < 5; j++) {
        g_UiFormatBuffer[i] = D_801457E8[D_801F2948[5]][j];
        i++;
    }
    g_UiFormatBuffer[i] = STRING_END;
    UI_DrawText(0x32, 0x1E, 0, 0xFF, g_UiFormatBuffer);
    UI_DrawText(0x32, 0x42, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 227 + (s8)D_801DB0B4));
}

MATCH void func_801D5D5C(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3States, D_801F294C);
}

/* func_801D5D98 */
MATCH void Menu_StartFairyEventMessage(void) {
    u8* state = &g_GameStateIndex;

    if (*state != 2) {
        Message_StartAreaMessage(0xEE);
        *state = 2;
        D_801F294C += 1;
    }
}

MATCH void func_801D5DF4(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3Step1Funcs, D_801F294D);
}

/* func_801D5E30 */
MATCH void Menu_ConfirmFairy(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        D_801DB0C4 = 4;
        D_801DB0B4 = 0;
        D_801DB0C8 = 0xF0;
        D_801F294D += 1;
    }
}

MATCH void func_801D5E94(void) {
    s8 count;
    u8 check;

    count      = D_801DB0C4 - 1;
    D_801DB0C4 = count;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x10 - ((count & BYTE_MASK) * 8)) & 0xFFF8, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    func_801D830C(0x44 - ((u8)D_801DB0C4 * 0x1E), 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
    func_801D8058(0x4A, 0x64 - ((u8)D_801DB0C4 * 0x1E));
    check = D_801DB0C4;
    if (check == 0) {
        D_801F294D += 1;
    }
}

MATCH void func_801D5F7C(void) {
    s32 pressed;

    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        D_801DB0C8 = 0xF1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x04));
        D_801DB0B8 = 0;
        D_801F294D += 1;
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x06));
        D_801F294D = 8;
    } else {
        pressed = INPUT_GetRepeatedButtons(g_InputPressed & 0xA000);
        if (pressed & HALF_MASK) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
        }
        if (pressed & 0x8000) {
            D_801DB0B4 -= 1;
            if ((s8)D_801DB0B4 < 0) {
                D_801DB0B4 = Fairy_CountFairies() - 1;
            }
        } else if (pressed & 0x2000) {
            D_801DB0B4 += 1;
            if ((s8)D_801DB0B4 >= (Fairy_CountFairies() & BYTE_MASK)) {
                D_801DB0B4 = 0;
            }
        }
    }
    func_801D812C();
    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
    func_801D8058(0x4A, 0x64);
    func_801D88A4(((s8)D_801DB0B4 * 8) + 0x55, 0x6D, 0);
}

MATCH void func_801D6124(void) {
    u16 cue;

    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (D_801DB0B8 == 1) {
            cue = 0x104;
            goto play_cue;
        }
        D_801DB0C8 = -1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x04));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        D_801DB0C4 = 0;
        D_801F294D += 1;
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        cue = 0x106;
    play_cue:
        D_801DB0C8 = 0xF0;
        SND_PlayCue(cue);
        D_801F294D -= 1;
    } else if (INPUT_GetRepeatedButtons(g_InputPressed & 0xA000) & HALF_MASK) {
        D_801DB0B8 ^= 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    }
    if (D_801DB0C8 != 0xFFFF) {
        func_801D812C();
        if (D_801DB0C8 == 0xF1) {
            Menu_DrawCursorSprite(((s32)D_801DB0B8 * 32 + 0xF4) & 0xFFFC, 0x15, 0);
        }
        func_801D8058(0x4A, 0x64);
        func_801D88A4(((s8)D_801DB0B4 * 8) + 0x55, 0x6D, 1);
    }
    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
}

MATCH void func_801D62C8(void) {
    s8 step;

    step       = D_801DB0C4 + 1;
    D_801DB0C4 = step;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x10 - ((step & BYTE_MASK) * 8)) & 0xFFF8, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    func_801D8058(0x4A, ((u8)D_801DB0C4 * 0x28) + 0x64);
    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
    if ((u8)D_801DB0C4 == 4) {
        D_801DB0C4 = 5;
        D_801F294D = 7;
    }
}

MATCH void func_801D6390(void) {
    u8 value;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (D_801F2944 == 0) {
            value = 6;
        } else {
            D_801DB0C4 = 5;
            value      = 7;
        }
        D_801F294D = value;
    }
    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
}

MATCH void func_801D640C(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3Step1Sub6Funcs, D_801F294E);
}

MATCH void func_801D6448(void) {
    s32 i;

    Fairy_GenerateName();
    for (i = 0; i < 6; i++) {
        g_TextVariables[0][i] = D_801DB080[i];
    }
    Message_StartAreaMessage(0xF3);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    D_801F294E++;
    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
}

MATCH void func_801D64E0(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (D_801F2945 != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
            D_801DB0C4 = 0;
            D_801F294E += 1;
        } else {
            D_801F294E = 0;
        }
    }
    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
}

MATCH void func_801D6574(void) {
    D_801DB0C4 = D_801DB0C4 + 1;
    func_801D830C(0x44 - ((u8)D_801DB0C4 * 0x1E), 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA8E8();
    }
}

MATCH void func_801D65F8(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3Step1Sub7Funcs, D_801F294E);
}

INCLUDE_ASM(func_801D6634);

MATCH void func_801D67F0(void) {
    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 1);
    func_801AE214((D_801DB0D0 * 8) + 0x4A, 0x42, 8, 0);
    func_801D97C8(D_801DAAA8, 0xB0, 0x2B);
    func_801D9B80(0x12, 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, 0x67, D_801DB0D4, D_801DB0D8);
    D_801DB0DC = func_801DA114();
}

MATCH void func_801D68AC(void) {
    s32 i;

    D_801DB0C4 = D_801DB0C4 + 1;
    if (D_801DB0DC != 0) {
        func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 1);
    } else {
        func_801D830C(0x44 - (D_801DB0C4 * 0x1E), 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 1);
    }
    func_801D97C8(D_801DAAA8, (D_801DB0C4 * 0x1E) + 0xB0, 0x2B);
    func_801D9B80(0x12, (D_801DB0C4 * 0x1E) + 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, (D_801DB0C4 * 0x1E) + 0x67, D_801DB0D4, D_801DB0D8);
    if (D_801DB0C4 == 4) {
        if (D_801DB0DC != 0) {
            if (D_801DB080[0] == 0) {
                for (i = 0; i < 5; i++) {
                    D_801DB080[i] = g_Fairies[Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK][i];
                }
            }
            Message_StartAreaMessage(244);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            D_801F294E += 1;
        } else {
            Message_StartAreaMessage(247);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            D_801F294C       = 4;
            D_801F294D       = 0;
        }
    }
}

MATCH void func_801D6AC8(void) {
    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 1);
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
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
    D_801DB0C4 = D_801DB0C4 + 1;
    func_801D830C(0x44 - ((u8)D_801DB0C4 * 0x1E), 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 1);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA8E8();
    }
}

MATCH void func_801D6BE4(void) {
    s8 step;

    step       = D_801DB0C4 + 1;
    D_801DB0C4 = step;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x10 - ((step & BYTE_MASK) * 8)) & 0xFFF8, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    func_801D830C(0x20 - ((u8)D_801DB0C4 * 0x1E), 0x32, Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK, 0);
    func_801D8058(0x4A, 0x64 - ((u8)D_801DB0C4 * 0x1E));
    if ((u8)D_801DB0C4 == 4) {
        Message_StartAreaMessage(0xF7);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        D_801F294C       = 4;
        D_801F294D       = 0;
    }
}

MATCH void func_801D6CDC(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3Step2Funcs, D_801F294D);
}

INCLUDE_ASM(func_801D6D18);

INCLUDE_ASM(func_801D6E70);

MATCH void func_801D708C(void) {
    u16 cue;

    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (D_801DB0B8 == 1) {
            cue = 0x104;
            goto play_cue;
        }
        D_801DB0C8 = -1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x04));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        D_801DB0C4 = 0;
        D_801F294D += 1;
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        cue = 0x106;
    play_cue:
        D_801DB0C8 = 0xF0;
        SND_PlayCue(cue);
        D_801F294D -= 1;
    } else if (INPUT_GetRepeatedButtons(g_InputPressed & 0xA000) & HALF_MASK) {
        D_801DB0B8 ^= 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    }
    if (D_801DB0C8 != 0xFFFF) {
        func_801D812C();
        if (D_801DB0C8 == 0xF1) {
            Menu_DrawCursorSprite(((s32)D_801DB0B8 * 32 + 0xF4) & 0xFFFC, 0x15, 0);
        }
    }
    func_801D9210();
    func_801D9348(((D_801DB0B4 & 1) * 0x88) + 0x20, ((((s32)(D_801DB0B4 << 0x18) >> 0x19) * 0x38) + 0x2B) & HALF_MASK, 0, 6);
}

INCLUDE_ASM(func_801D7234);

MATCH void func_801D73F8(void) {
    u8 value;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (D_801F2944 == 0) {
            value = 6;
        } else {
            D_801DB0C4 = 4;
            value      = 7;
        }
        D_801F294D = value;
    }
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & BYTE_MASK, 0);
}

MATCH void func_801D7474(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3Step2Sub6Funcs, D_801F294E);
}

MATCH void func_801D74B0(void) {
    s32 i;

    Fairy_GenerateName();
    for (i = 0; i < 6; i++) {
        g_TextVariables[0][i] = D_801DB080[i];
    }
    Message_StartAreaMessage(0xF3);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    D_801F294E++;
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & BYTE_MASK, 0);
}

MATCH void func_801D7548(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (D_801F2945 != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
            D_801DB0C4 = 0;
            D_801F294E += 1;
        } else {
            D_801F294E = 0;
        }
    }
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & BYTE_MASK, 0);
}

MATCH void func_801D75DC(void) {
    D_801DB0C4 = D_801DB0C4 + 1;
    func_801D90D8(0x20 - ((u8)D_801DB0C4 * 0x28), 0x2B, func_801D92F4(D_801DB0B4) & BYTE_MASK, 0);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA7A4();
    }
}

MATCH void func_801D7660(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3Step2Sub7Funcs, D_801F294E);
}

INCLUDE_ASM(func_801D769C);

MATCH void func_801D7878(void) {
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & BYTE_MASK, 1);
    func_801AE214((D_801DB0D0 * 8) + 0x5B, 0x50, 8, 0);
    func_801D97C8(D_801DAAA8, 0xB0, 0x2B);
    func_801D9B80(0x12, 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, 0x67, D_801DB0D4, D_801DB0D8);
    D_801DB0DC = func_801DA114();
}

INCLUDE_ASM(func_801D7934);

MATCH void func_801D7B50(void) {
    func_801D90D8(0x20, 0x2B, func_801D92F4(D_801DB0B4) & BYTE_MASK, 1);
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
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
    D_801DB0C4 = D_801DB0C4 + 1;
    func_801D90D8(0x20 - ((u8)D_801DB0C4 * 0x1E), 0x2B, func_801D92F4(D_801DB0B4) & BYTE_MASK, 1);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA7A4();
    }
}

INCLUDE_ASM(func_801D7C6C);

/* func_801D7DD4 */
MATCH void Menu_StartFairyEndMessage(void) {
    u8* state = &g_GameStateIndex;

    if (*state != 2 && D_801F294D == 0) {
        Message_StartAreaMessage(0xF6);
        *state = 2;
    }
}

/* func_801D7E30 */
MATCH void Fairy_EndCommuSceneEvent3(void) {
    COMMU_ADVANCE_STEP();
}

#include "overlays/commu/Fairy_CountFairies.h"

/* func_801D7EA0 */
MATCH u8 Fairy_FindActiveJob(u8 arg) {
    s32 active_count;
    s32 i;

    active_count = 0;
    for (i = 0; i < 0x3C; i++) {
        if (g_FairyJobs[i].active != 0) {
            if ((active_count & 0xFF) == arg) {
                return (u8)i;
            }
            active_count++;
        }
    }
    return 0xFF;
}

#include "overlays/commu/Commu_CellGrid.h"

MATCH void func_801D7EF0(s16 x, s16 y) {
    s32 i;
    s32 offset;

    COMMU_DRAW_CELL_GRID(func_801D875C, 0x16, 20, 2, 6);
}

INCLUDE_ASM(func_801D8058);

INCLUDE_ASM(func_801D812C);

MATCH void func_801D81A4(s16 x, s16 y) {
    s32 i;
    s32 offset;

    COMMU_DRAW_CELL_GRID(func_801D875C, 0x22, 7, 4, 6);
}

INCLUDE_ASM(func_801D830C);

INCLUDE_ASM(func_801D851C);

INCLUDE_ASM(func_801D875C);

MATCH void func_801D88A4(s32 x, s32 y, s32 bright) {
    POLY_F3* poly;
    u8       colour;

    COMMU_DRAW_CURSOR_TRIANGLE(x, y, bright);
}

/* Fills D_801DB080 with a name built from one random half of each of the two name tables in the loaded text bank. */
/* func_801D8968 */
MATCH void Fairy_GenerateName(void) {
    u8  count;
    s32 i;
    u8* src;
    u8* dst;

    count = 0;
    i     = 5;
    dst   = &D_801DB080[i];
    do {
        *dst = 0;
        i -= 1;
        dst -= 1;
    } while (i >= 0);

    src = MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FAIRY_NAME_FIRST_HALF_INDEX + RANDOM_MASK(0x3F));
    for (;;) {
        u8 ch;

        ch = *src;
        if (ch == 0) {
            break;
        }
        D_801DB080[count] = ch;
        count++;
        src++;
    }

    src = MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FAIRY_NAME_SECOND_HALF_INDEX + RANDOM_MASK(0x3F));
    for (;;) {
        u8 ch;

        ch = *src;
        if (ch == 0) {
            break;
        }
        D_801DB080[count] = ch;
        count++;
        src++;
    }
}

INCLUDE_ASM(Menu_DrawHeaderBar);

#include "shared/Menu_DrawPortrait.h"

INCLUDE_ASM(func_801D90D8);

MATCH void func_801D9210(void) {
    s32 drawn;
    u32 i;

    drawn = 0;
    for (i = 0; i < 7; i++) {
        if (g_Characters[i].unk_07 & 1) {
            func_801D90D8(((drawn & 1) * 0x88) + 0x20, (((u8)drawn >> 1) * 0x38) + 0x2B, (u8)i, 0);
            drawn++;
        }
    }
}

MATCH u8 func_801D92B0(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (g_Characters[i].unk_07 & 1) {
            count++;
        }
    }
    return count;
}

MATCH u8 func_801D92F4(u8 arg) {
    s32 active_count;
    s32 i;

    active_count = 0;
    for (i = 0; i < 7; i++) {
        if (g_Characters[i].unk_07 & 1) {
            if ((active_count & 0xFF) == arg) {
                return (u8)i;
            }
            active_count++;
        }
    }
    return 0xFF;
}

INCLUDE_ASM(func_801D9348);

INCLUDE_ASM(func_801D94D0);

INCLUDE_ASM(func_801D97C8);

MATCH void Menu_DrawPanelIcon(s16 x, s16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

INCLUDE_ASM(func_801D9B80);

INCLUDE_ASM(func_801DA114);

INCLUDE_ASM(func_801DA7A4);

INCLUDE_ASM(func_801DA8E8);
