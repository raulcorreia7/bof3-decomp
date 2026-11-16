#include "commu02_08.h"
#include "overlays/commu/Commu_CursorTriangle.h"
#include "common/util.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

void func_801D4910(s32 x, s32 y);
void func_801D4EA4(s32 left, s32 top, s32 icon_row, s32 raised);
void func_801D8058(s32 left, s32 top);
void func_801D2908(s16 x, s16 y, u8 mode);
void func_801D2FA4(s16 x, s16 y);
void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color);

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

    func_801D3184(38, 16);
    func_801D32A0(168, 16, 0);
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

MATCH void func_801D15A4(void) {
    s32 i;
    u8  n;
    u32 r;
    s32 bit;
    s32 off;
    s32 base;

    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    D_801DB0C4 -= 1;
    for (i = 0; i < (s8)D_801DB0B4; i++) {
        func_801D2CF8((i * 0x200000 + 0x100000) >> 16, 0x6C, 0xFF);
    }
    base = (s8)D_801DB0B4 * 32;
    off  = D_801DB0C4 * 16 - 16;
    func_801D2CF8(base - off, 0x6C, 0xFF);
    if (D_801DB0C4 == 0) {
        D_801DB0B4 += 1;
        if ((s8)D_801DB0B4 == 9) {
            D_801DB0B8 = 0;
            if ((rand() & 3) == 0) {
                r = rand() & 0xF;
                if (r < 8) {
                    n = 1;
                } else if (r < 0xE) {
                    n = 2;
                } else {
                    n = 3;
                }
                while (n != 0) {
                    bit = rand() & 7;
                    if (((D_801DB0B8 >> bit) & 1) == 0) {
                        D_801DB0B8 |= 1 << bit;
                        n--;
                    }
                }
            }
            D_801F294E += 1;
        } else {
            SND_PlayCue(0x102);
            D_801DB0C4 = 2;
        }
    }
}

MATCH void func_801D1774(void) {
    s32 i;
    s32 j;
    s32 x;

    func_801D2794(9, 1, 0);
    for (i = 0; i < 8; i++) {
        if ((D_801DB0B8 >> i) & 1) {
            j = i + 1;
            x = (s16)(0x30 + i * 0x20);
            func_801D2CF8(x, 0x6C, D_801DB080[j]);
        }
    }
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    MESSAGE_START_WAIT(MSG_115);
    D_801F294E += 1;
}

MATCH void func_801D184C(void) {
    s32 i;
    s32 j;
    s32 x;

    func_801D2794(9, 1, 0);
    for (i = 0; i < 8; i++) {
        if ((D_801DB0B8 >> i) & 1) {
            j = i + 1;
            x = (s16)(0x30 + i * 0x20);
            func_801D2CF8(x, 0x6C, D_801DB080[j]);
        }
    }
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x102));
        D_801DB0C4 = 4;
        D_801F294E += 1;
    }
}

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

#ifdef NON_MATCHING
NON_MATCHING void func_801D1A50(void) {
    u16* input;
    u16  repeated;
    s32  slot;

    FAKE_STACK_PADS(u8, 1); /* FAKE: retail reserves 8 unused stack bytes. */

    input    = &g_InputPressed;
    repeated = INPUT_GetRepeatedButtons(*input & 0xA000);
    if (repeated != 0) {
        if ((s8)D_801DB0B4 < 8) {
            SND_PlayCue(0x100);
            if (LOB(D_801DB0B4) != 0) {
                if (repeated & 0x8000) {
                    D_801DB0B8 = (u8)D_801DB0B8 - 1;
                    if (D_801DB0B8 < 0) {
                        D_801DB0B8 = 2;
                    }
                } else if (repeated & 0x2000) {
                    D_801DB0B8 = (u8)D_801DB0B8 + 1;
                    if (D_801DB0B8 >= 3) {
                        D_801DB0B8 = 0;
                    }
                }
            } else {
                D_801DB0B8 ^= 1;
            }
        }
    } else if (*input & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (D_801DB0B8 == 2) {
            SND_PlayCue(0x104);
            SND_PlayCue(0x102);
            D_801DB0C4 = 0;
            D_801F294D++;
        } else if ((slot = LOB(D_801DB0B4)) < 8) {
            D_801DB080[10 + slot] = (u8)D_801DB0B8;
            D_801DB0B4++;
            SND_PlayCue(0x103);
            if ((s8)D_801DB0B4 == 8) {
                D_801DB0B8 = 2;
            }
        }
    } else if (*input & g_InputMasks[MENU_INPUT_CANCEL]) {
        if (LOB(D_801DB0B4) != 0) {
            SND_PlayCue(0x106);
            D_801DB0B4--;
            if ((s8)D_801DB0B4 == 0 && D_801DB0B8 == 2) {
                D_801DB0B8 = 0;
            }
        }
    }

    if ((s8)D_801DB0B4 <= 0) {
        func_801D2908(0x58, 0x44, 2);
    } else if ((s8)D_801DB0B4 >= 8) {
        func_801D2908(0x58, 0x44, 3);
    } else {
        func_801D2908(0x58, 0x44, 0xFF);
    }
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    func_801D2794(9, 1, D_801DB0B4);
    if ((s8)D_801DB0B4 < 8) {
        func_801D269C(((s8)D_801DB0B4 << 5) + 0x40, 0x6E);
    }
    Menu_DrawCursorSprite(((D_801DB0B8 * 3) << 4) + 0x5E & 0xFFFE, 0x4A, 0);
}
#else
INCLUDE_ASM(func_801D1A50);
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801D1D68(void) {
    s32 i;
    u8  cnt;

    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    func_801D2794((u8)(D_801DB0B4 + 1), 1, D_801DB0B4);
    cnt        = D_801DB0C4 + 1;
    i          = (s8)D_801DB0B4 + 1;
    D_801DB0C4 = cnt;
    for (; i < 9; i++) {
        func_801D2CF8(((i << 21) + 0x100000) >> 16, D_801DB0C4 * 40 + 0x6C, 0xFF);
    }
    func_801D2908(0x58, 0x44 - D_801DB0C4 * 40, 2);
    if (D_801DB0C4 == 4) {
        D_801DB0C4 = 0x1E;
        D_801DB0BC = 1;
        D_801F294D += 1;
    }
}
#else
INCLUDE_ASM(func_801D1D68);
#endif

MATCH void func_801D1E98(void) {
    s32 idx;
    u8  old;
    s32 lt;

    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
    D_801DB0C4 -= 1;
    if (D_801DB0C4 == 0) {
        idx = (s8)D_801DB0BC;
        lt  = D_801DB080[idx - 1] < D_801DB080[idx];
        if (D_801DB080[idx + 9] == (lt ^ 1)) {
            SND_PlayCue(0x104);
            old        = D_801DB0BC;
            D_801DB0BC = old + 1;
            if ((s8)D_801DB0BC == (s8)D_801DB0B4 + 1) {
                D_801DB0BC = old;
                D_801DB0C0 = 0;
                D_801DB0C4 = 0x3C;
                D_801F294D += 1;
            } else {
                D_801DB0C4 = 0x1E;
            }
        } else {
            SND_PlayCue(0x107);
            D_801DB0C0 = 1;
            D_801DB0C4 = 0x3C;
            D_801F294D += 1;
        }
    }
    func_801D2794((u8)(D_801DB0B4 + 1), (u8)D_801DB0BC, D_801DB0B4);
}

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

MATCH void func_801D2078(void) {
    s32 i;

    D_801DB0C4 += 1;
    i = 0;
    if ((s8)D_801DB0B4 >= 0) {
        do {
            func_801D2CF8((i * 0x200000 + 0x100000) >> 16, D_801DB0C4 * 40 + 0x6C, D_801DB080[i]);
            i++;
        } while (i <= (s8)D_801DB0B4);
    }
    if (D_801DB0C4 == 4) {
        if (D_801DB0C0 != 0) {
            D_801DB07C = 0;
            Message_StartAreaMessage(MSG_116);
        } else {
            D_801DB07C = (D_801DB07C * D_801DAC34[D_801448F2][(s8)D_801DB0BC - 1] + 50) / 100;
            Message_StartAreaMessage(MSG_118);
        }
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        D_801F294D += 1;
    }
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
}

MATCH void func_801D21FC(void) {
    u8* state = &g_GameStateIndex;

    if (*state != GAME_REQUEST_MESSAGE) {
        if (D_801DB07C >= 0x2710) {
            Message_StartAreaMessage(MSG_121);
            *state = GAME_REQUEST_MESSAGE;
            D_801F294D += 1;
        } else {
            Message_StartAreaMessage(MSG_120);
            *state     = GAME_REQUEST_MESSAGE;
            D_801F294D = 3;
        }
    }
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
}

MATCH void func_801D22A4(void) {
    u8* state = &g_GameStateIndex;

    if (*state != GAME_REQUEST_MESSAGE) {
        Party_AddZenny(D_801DB07C, 0);
        Message_StartAreaMessage(MSG_117);
        D_801DB07C = 0;
        *state     = GAME_REQUEST_MESSAGE;
    }
    func_801D3184(0x26, 0x10);
    func_801D32A0(0xA8, 0x10, 0);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801D2320(void) {
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
#else
INCLUDE_ASM(func_801D2320);
#endif

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
        step  = &g_SceneEventState.step;
        *step = *step + 1;
    }
}

MATCH void func_801D269C(s32 x, s32 y) {
    POLY_F3* poly;
    u8       colour;

    if ((g_FrameCount & 8) != 0) {
        colour = ((g_FrameCount & 6) << 5) | 0x3F;
    } else {
        colour = ((~g_FrameCount & 6) << 5) | 0x3F;
    }
    poly = g_GfxPrimCursor;
    SetPolyF3(poly);
    setXY3(poly, x, y, x - 6, y - 6, x + 6, y - 6);
    setRGB0(poly, 0, colour, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_F3));
}

MATCH s32 func_801D2750(s32 limit) {
    s32 roll;

    do {
        roll = RANDOM_MASK(0xF);
    } while (roll == 0 || roll >= ((limit & BYTE_MASK) + 1));
    return roll;
}

MATCH void func_801D2794(s32 count, s32 shown, s32 chosen) {
    s32 i;
    s32 y;
    u8  selected;

    selected = chosen;
    for (i = 0; i < (u8)count; i++) {
        y = 0x6C;
        if (i <= selected && selected != 0 && i != 0) {
            if (D_801DB089[i] == 0) {
                y = 0x64;
            } else {
                y = 0x74;
            }
        }
        if (i < (u8)shown) {
            func_801D2CF8((s16)(0x10 + i * 0x20), y, D_801DB080[i]);
        } else {
            func_801D2CF8((s16)(0x10 + i * 0x20), y, 0xFF);
        }
    }
}

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

MATCH void func_801D2908(s16 x, s16 y, u8 mode) {
    switch (mode) {
        case 0xFF:
            func_801D2AC4(x, y, 0, 0);
            func_801D2AC4(x + 0x30, y, 1, 0);
            func_801D2AC4(x + 0x60, y, 2, 0);
            break;
        case 0:
            func_801D2AC4(x, y, 0, 1);
            func_801D2AC4(x + 0x30, y, 1, 2);
            func_801D2AC4(x + 0x60, y, 2, 0);
            break;
        case 1:
            func_801D2AC4(x, y, 0, 2);
            func_801D2AC4(x + 0x30, y, 1, 1);
            func_801D2AC4(x + 0x60, y, 2, 0);
            break;
        case 2:
            func_801D2AC4(x, y, 0, 0);
            func_801D2AC4(x + 0x30, y, 1, 0);
            func_801D2AC4(x + 0x60, y, 2, 2);
            break;
        case 3:
            func_801D2AC4(x, y, 0, 2);
            func_801D2AC4(x + 0x30, y, 1, 2);
            func_801D2AC4(x + 0x60, y, 2, 0);
            break;
    }
}

INCLUDE_ASM(func_801D2AC4);

MATCH void func_801D2CF8(s32 x, s32 y, s32 icon) {
    SPRT* sprite;
    u8    index;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256), NULL);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x, y);
    setWH(sprite, 32, 40);
    setRGB0(sprite, 0x80, 0x80, 0x80);
    index = icon;
    if (index == GAME_NONE) {
        setUV0(sprite, 0, 0);
        sprite->clut = 0x7BC8;
    } else {
        setUV0(sprite, (icon & 7) * 32, (index / 8) * 40);
        sprite->clut = 0x7BC9;
    }
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}

MATCH void func_801D2E10(void) {
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    MESSAGE_START_WAIT(MSG_114);
    D_801F294D = 0;
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
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
}

/* Queues the 128-grey sprite whose source rectangle is entry index of the rectangle table. */
MATCH void FairyCasino_DrawFramePiece(s32 x, s32 y, s32 index) {
    SPRT* sprt;

    sprt = g_GfxPrimCursor;
    SetSprt(sprt);
    index = (u8)index * 4;
    setXY0(sprt, x, y);
    setWH(sprt, D_801DAC60[index + 2], D_801DAC60[index + 3]);
    setRGB0(sprt, 128, 128, 128);
    setUV0(sprt, D_801DAC60[index], D_801DAC60[index + 1]);
    sprt->clut = 0x7887;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}

#ifdef NON_MATCHING
NON_MATCHING void func_801D2FA4(s16 x, s16 y) {
    s32 i;
    s32 off;
    s32 tpage;
    s16 y2;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x2D;
    } else {
        tpage = 0x1D;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    GFX_AddPrim(GFX_LAYER_UI, 0xC);
    FairyCasino_DrawFramePiece(x, (s16)y, 0);
    off = 0x20;
    for (i = 0; i < 6; i++) {
        FairyCasino_DrawFramePiece((s16)(x + off), (s16)y, 1);
        off += 8;
    }
    FairyCasino_DrawFramePiece((s16)(x + 0x50), (s16)y, 2);
    FairyCasino_DrawFramePiece((s16)(x + 0x68), (s16)y, 3);
    off = 0x18;
    for (i = 0; i < 2; i++) {
        FairyCasino_DrawFramePiece(x, (s16)(y + off), 4);
        FairyCasino_DrawFramePiece((s16)(x + 0x68), (s16)(y + off), 5);
        off += 6;
    }
    y2 = y + 0x23;
    FairyCasino_DrawFramePiece(x, y2, 6);
    off = 8;
    for (i = 0; i < 12; i++) {
        FairyCasino_DrawFramePiece((s16)(x + off), y2, 7);
        off += 8;
    }
    FairyCasino_DrawFramePiece((s16)(x + 0x68), (s16)(y + 0x23), 8);
}
#else
INCLUDE_ASM(func_801D2FA4);
#endif

MATCH void func_801D3184(s32 x, s32 y) {
    UI_DrawWindow(x + 1, y + 1, 0x6A, 0x28, 0x80, g_WindowStyle);
    func_801D2FA4(x, y);
    UI_DrawText(x + 0x24, y + 7, 0, 4, D_801DACA8);
    sprintf(g_UiFormatBuffer, D_801D0C04, g_Zenny);
    y = (s16)(y + 0x18);
    UI_DrawAsciiString(x + 0x16, y, 0, g_UiFormatBuffer);
    UI_DrawText(x + 0x4E, y, 0, 1, D_801DACAC);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801D32A0(s32 x, s32 y, u8 mode) {
    s32 x2;
    s32 y2;
    u8* buf;
    s16 ox;
    s32 oy;

    UI_DrawWindow(x + 1, y + 1, 0x6A, 0x28, 0x80, g_WindowStyle);
    func_801D2FA4(x, y);
    UI_DrawText(x + 0x2C, y + 7, 0, 3, D_801DACB0);
    x2 = x;
    y2 = y;
    switch (mode) {
        case 2:
            if (D_801DB07C < 10) {
                sprintf(buf = g_UiFormatBuffer, D_801D0C08, D_801DB07C);
                ox = x + 0x3E;
            } else {
                sprintf(buf = g_UiFormatBuffer, D_801D0C04, D_801DB07C);
                ox = x + 0x16;
            }
            oy = y + 0x18;
            break;
        case 3:
            if (D_801DB07C < 100) {
                sprintf(buf = g_UiFormatBuffer, D_801D0C10, D_801DB07C);
                ox = x + 0x36;
            } else {
                sprintf(buf = g_UiFormatBuffer, D_801D0C04, D_801DB07C);
                ox = x + 0x16;
            }
            oy = y + 0x18;
            break;
        case 4:
            if (D_801DB07C < 1000) {
                sprintf(buf = g_UiFormatBuffer, D_801D0C18, D_801DB07C);
                ox = x + 0x2E;
            } else {
                sprintf(buf = g_UiFormatBuffer, D_801D0C04, D_801DB07C);
                ox = x + 0x16;
            }
            oy = y + 0x18;
            break;
        default:
            sprintf(buf = g_UiFormatBuffer, D_801D0C04, D_801DB07C);
            ox = x2 + 0x16;
            oy = y2 + 0x18;
            break;
    }
    UI_DrawAsciiString(ox, oy, 0, buf);
    UI_DrawText(x2 + 0x4E, y2 + 0x18, 0, 1, D_801DACB4);
}
#else
INCLUDE_ASM(func_801D32A0);
#endif

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
        MESSAGE_START_WAIT(MSG_127);
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

MATCH void func_801D3864(void) {
    s32  i;
    s32  j;
    u8*  p;
    u8   v;
    s32  zenny;
    s32* zp;

    i          = 0;
    p          = D_801DB080;
    zp         = &g_Zenny;
    zenny      = *zp;
    D_801DB07C = 500;
    *zp        = zenny - 500;
    for (; i < 3; i++, p++) {
        do {
            v  = func_801D2750(9);
            *p = v;
            if (i == 0) {
                break;
            }
            for (j = 0; j < i; j++) {
                if (D_801DB080[j] == v) {
                    break;
                }
            }
        } while (j != i);
    }
    D_801DB0B4 = 0;
    for (i = 3; i < 0x2B; i++) {
        D_801DB080[i] = 1;
    }
    func_801D4AE0(0x10, 0x18, 0);
    func_801D2CF8(0x68, 0x40, 0xFF);
    func_801D3184(0xCC, 0x10);
    func_801D32A0(0xCC, 0x3C, 0);
    D_801DB0C4 = 4;
    SND_PlayCue(0x102);
    D_801F294E += 1;
}

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
    MESSAGE_START_WAIT(MSG_128);
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

MATCH void func_801D3C30(void) {
    u16  buttons;
    s32  k;
    u8   val;
    u16* pad;

    pad     = &g_InputPressed;
    buttons = INPUT_GetRepeatedButtons(*pad & 0xF000);
    if (buttons != 0) {
        SND_PlayCue(0x100);
        k = (s8)D_801DB0B4 * 5 + 3;
        k += (u8)D_801DB0B8;
        if (buttons & PADLdown) {
            val               = D_801DB080[(u8)k] - 1;
            D_801DB080[(u8)k] = val;
            if ((s8)val <= 0) {
                D_801DB080[(u8)k] = 9;
            }
        } else if (buttons & PADLup) {
            val               = D_801DB080[(u8)k] + 1;
            D_801DB080[(u8)k] = val;
            if (val >= 10) {
                D_801DB080[(u8)k] = 1;
            }
        } else if (buttons & PADLright) {
            D_801DB0B8 += 1;
            if (D_801DB0B8 >= 3) {
                D_801DB0B8 = 0;
            }
        } else if (buttons & PADLleft) {
            D_801DB0B8 -= 1;
            if (D_801DB0B8 < 0) {
                D_801DB0B8 = 2;
            }
        }
    } else if (*pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(0x104);
        D_801F294D += 1;
    }
    func_801D4AE0(0x10, 0x18, 0);
    func_801D4F88(0x68, 0x40, 0);
    func_801D4EA4(0x68, 0x78, D_801DB0B4, 1);
    func_801D3184(0xCC, 0x10);
    func_801D32A0(0xCC, 0x3C, 0);
}

INCLUDE_ASM(func_801D3E44);

MATCH void func_801D4158(void) {
    u8* state;
    u8* src_base;
    u8* dst_base;
    u8* src_item;
    u8* dst_item;
    u8  value;
    s32 i;
    s32 offset;

    state = &g_GameStateIndex;
    if (*state != 2) {
        D_801DB0B4 += 1;
        if ((s8)D_801DB0B4 < 8) {
            dst_base = &D_801DB080[3];
            src_base = dst_base - 5;
            i        = 0;
            do {
                offset   = (s8)D_801DB0B4 * 5;
                dst_item = (u8*)(offset + (s32)dst_base + i);
                src_item = (u8*)(offset + (s32)src_base + i);
                value    = *src_item;
                i++;
                *dst_item = value;
            } while (i < 3);
            D_801F294D = 1;
        } else {
            Message_StartAreaMessage(MSG_133);
            *state = 2;
            D_801F294D += 1;
        }
        func_801D4AE0(16, 24, 0);
        func_801D4EA4(104, 120, (u8)(D_801DB0B4 - 1), 0);
    } else {
        func_801D4AE0(16, 24, 1);
        func_801D4EA4(104, 120, D_801DB0B4, 0);
    }
    func_801D4F88(104, 64, 0);
    func_801D3184(204, 16);
    func_801D32A0(204, 60, 0);
}

MATCH void func_801D42B4(void) {
    u8* state;

    state = &g_GameStateIndex;
    if (*state != GAME_REQUEST_MESSAGE) {
        Message_StartAreaMessage(MSG_134);
        *state     = GAME_REQUEST_MESSAGE;
        D_801F294D = 8;
    }
    func_801D4AE0(16, 24, 1);
    func_801D4F88(104, 64, 1);
    if ((s8)D_801DB0B4 == 8) {
        func_801D4EA4(104, 120, 7, 0);
    } else {
        func_801D4EA4(104, 120, (u8)D_801DB0B4, 0);
    }
    func_801D3184(204, 16);
    func_801D32A0(204, 60, 0);
}

MATCH void func_801D437C(void) {
    u8* state;
    s32 idx;

    state = &g_GameStateIndex;
    if (*state != GAME_REQUEST_MESSAGE) {
        idx = ((s8)D_801DB0B4 * 3 + (s8)D_801DB0B8) * 2 + D_801448F2 * 48;
        if (!(u8)Item_Add(D_801DAD00[0][idx + 1], D_801DAD00[0][idx], 1, 0)) {
            Message_StartAreaMessage(MSG_131);
            *state = GAME_REQUEST_MESSAGE;
        }
        D_801F294D = 6;
    }
    func_801D4AE0(0x10, 0x18, 1);
    func_801D4F88(0x68, 0x40, 1);
    func_801D4EA4(0x68, 0x78, D_801DB0B4, 0);
    func_801D3184(0xCC, 0x10);
    func_801D32A0(0xCC, 0x3C, 0);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801D448C(void) {
    s32 selected;
    u8  value;

    selected = (s8)D_801DB0B4;
    if (selected == 8) {
        selected = 7;
    }
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (D_801F294E == 0) {
            D_801DB0C4 = 0;
            func_801D4F88(104, 64, 1);
            func_801D4EA4(104, 120, (u8)selected, 0);
            func_801D4AE0(16, 24, 1);
            func_801D3184(204, 16);
            func_801D32A0(204, 60, 0);
            D_801F294E += 1;
        } else if (D_801F294E == 1) {
            value      = D_801DB0C4 + 1;
            D_801DB0C4 = value;
            selected   = (u8)selected * 5;
            func_801D2CF8(168 - ((u8)value * 16), 120 - ((u8)value * 14), D_801DB080[selected + 5]);
            func_801D2CF8(136 - ((u8)D_801DB0C4 * 8), 120 - ((u8)D_801DB0C4 * 14), D_801DB080[selected + 4]);
            func_801D2CF8(104, 120 - ((u8)D_801DB0C4 * 14), D_801DB080[selected + 3]);
            func_801D2CF8(168 - ((u8)D_801DB0C4 * 16), 64, D_801DB080[selected + 2]);
            func_801D2CF8(136 - ((u8)D_801DB0C4 * 8), 64, D_801DB080[selected + 1]);
            func_801D2CF8(104, 64, D_801DB080[selected]);
            func_801D4AE0(16, 24, 1);
            func_801D3184(204, 16);
            func_801D32A0(204, 60, 0);
            if (D_801DB0C4 == 4) {
                if (D_801F294F == 0) {
                    D_801F294D = 0;
                    D_801F294E = 0;
                } else {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
                    D_801DB0C4 = 0;
                    D_801F294E = 2;
                }
            }
        } else {
            value      = D_801DB0C4 + 1;
            D_801DB0C4 = value;
            func_801D4AE0(16 - ((u8)value * 30), 24, 0);
            func_801D3184(204 + ((u8)D_801DB0C4 * 30), 16);
            func_801D32A0(204 + ((u8)D_801DB0C4 * 30), 60, 0);
            func_801D2CF8(104, 64 - ((u8)D_801DB0C4 * 30), 0xFF);
            if (D_801DB0C4 == 5) {
                D_801F294C = 2;
                D_801F294D = 0;
                D_801F294E = 0;
                D_801F294F = 0;
            }
        }
    } else {
        func_801D4F88(104, 64, 1);
        func_801D4EA4(104, 120, (u8)selected, 0);
        func_801D4AE0(16, 24, 1);
        func_801D3184(204, 16);
        func_801D32A0(204, 60, 0);
    }
}
#else
INCLUDE_ASM(func_801D448C);
#endif

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
        step  = &g_SceneEventState.step;
        *step = *step + 1;
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801D4910(s32 x, s32 y) {
    s32 i;
    s32 off;
    s32 tpage;
    s16 y2;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x2D;
    } else {
        tpage = 0x1D;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    GFX_AddPrim(GFX_LAYER_UI, 0xC);
    FairyCasino_DrawFramePiece((s16)x, (s16)y, 0xB);
    off = 8;
    for (i = 0; i < 9; i++) {
        FairyCasino_DrawFramePiece((s16)(x + off), (s16)(y - 1), 0xD);
        off += 8;
    }
    FairyCasino_DrawFramePiece((s16)(x + 0x4F), (s16)y, 0xC);
    off = 8;
    for (i = 0; i < 14; i++) {
        y2 = (s16)(y + off);
        FairyCasino_DrawFramePiece((s16)x, y2, 0xE);
        FairyCasino_DrawFramePiece((s16)(x + 0x50), y2, 0xF);
        off += 8;
    }
    y2 = (s16)(y + 0x78);
    FairyCasino_DrawFramePiece((s16)x, (s16)y2, 0x10);
    off = 8;
    for (i = 0; i < 9; i++) {
        FairyCasino_DrawFramePiece((s16)(x + off), (s16)y2, 0xD);
        off += 8;
    }
    FairyCasino_DrawFramePiece((s16)(x + 0x50), (s16)(y + 0x78), 0x11);
}
#else
INCLUDE_ASM(func_801D4910);
#endif
#ifdef NON_MATCHING
NON_MATCHING void func_801D4AE0(s16 x, s16 y, u8 flag) {
    s32 i;
    s32 dy;
    s32 gy;
    s16 ry;
    u8  k;
    s8  sel;

    UI_DrawWindow(x, y, 0x52, 0x7A, 0, g_WindowStyle);
    func_801D4910(x, y);
    dy = 7;
    gy = 9;
    for (i = 0; i < 8; i++) {
        k   = i * 5 + 3;
        sel = D_801DB0B4;
        if (i == sel) {
            if (flag == 0) {
                sprintf(g_UiFormatBuffer, D_801DAD60);
                ry = y + dy;
                UI_DrawAsciiString(x + 6, ry, 0, g_UiFormatBuffer);
                sprintf(g_UiFormatBuffer, D_801DAD64);
                UI_DrawAsciiString(x + 0x2F, ry, 2, g_UiFormatBuffer);
            } else {
                sprintf(g_UiFormatBuffer, D_801D0C24, D_801DB080[k], D_801DB080[k + 1], D_801DB080[k + 2]);
                ry = y + dy;
                UI_DrawAsciiString(x + 6, ry, 0, g_UiFormatBuffer);
                sprintf(g_UiFormatBuffer, D_801D0C20, D_801DB080[k + 3]);
                UI_DrawAsciiString(x + 0x2F, ry, 2, g_UiFormatBuffer);
                sprintf(g_UiFormatBuffer, D_801D0C20, D_801DB080[k + 4]);
            }
            UI_DrawAsciiString(x + 0x43, ry, 1, g_UiFormatBuffer);
            UI_DrawGlyphString(x + 0x39, y + gy, 0, D_801D0C2C);
        } else if (i < sel) {
            sprintf(g_UiFormatBuffer, D_801D0C24, D_801DB080[k], D_801DB080[k + 1], D_801DB080[k + 2]);
            ry = y + dy;
            UI_DrawAsciiString(x + 6, ry, 0, g_UiFormatBuffer);
            sprintf(g_UiFormatBuffer, D_801D0C20, D_801DB080[k + 3]);
            UI_DrawAsciiString(x + 0x2F, ry, 2, g_UiFormatBuffer);
            sprintf(g_UiFormatBuffer, D_801D0C20, D_801DB080[k + 4]);
            UI_DrawAsciiString(x + 0x43, ry, 1, g_UiFormatBuffer);
            UI_DrawGlyphString(x + 0x39, y + gy, 0, D_801D0C2C);
        } else {
            sprintf(g_UiFormatBuffer, D_801DAD60);
            ry = y + dy;
            UI_DrawAsciiString(x + 6, ry, 7, g_UiFormatBuffer);
            sprintf(g_UiFormatBuffer, D_801DAD64);
            UI_DrawAsciiString(x + 0x2F, ry, 7, g_UiFormatBuffer);
            UI_DrawAsciiString(x + 0x43, ry, 7, g_UiFormatBuffer);
            UI_DrawGlyphString(x + 0x39, y + gy, 7, D_801D0C2C);
        }
        gy += 14;
        dy += 14;
    }
}
#else
INCLUDE_ASM(func_801D4AE0);
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801D4EA4(s32 left, s32 top, s32 icon_row, s32 raised) {
    s32 i;
    s32 x;
    s32 draw_y;
    s32 up_y;
    u8  icon;
    u8* icons;

    icon  = (u8)icon_row * 5 + 3;
    up_y  = (top - 8) << 16;
    icons = D_801DB080;
    x     = left;
    for (i = 0; i < 3; i++) {
        if (D_801DB0B8 == i && (u8)raised != 0) {
            draw_y = up_y >> 16;
        } else {
            draw_y = top;
        }
        func_801D2CF8((s16)x, (s16)draw_y, icons[icon]);
        icon++;
        x += 32;
    }
}
#else
INCLUDE_ASM(func_801D4EA4);
#endif

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

#ifdef NON_MATCHING
NON_MATCHING void func_801D50E4(void) {
    s32 selection_offset;
    u8  bgm;
    u8  state;

    if (g_UiWindowEffectBusy != 0) {
        return;
    }
    bgm              = g_SndBGMId;
    g_AreaDrawFlags  = 0;
    D_801DB0CC       = bgm;
    selection_offset = bgm * BGM_TRACK_SIZE;
    SND_StopSequence(g_SelectionCues[selection_offset], g_SelectionSequences[selection_offset]);
    SND_RequestBGM(0x67);
    while (EMI_IsReady() == 0) {
        SYS_ThreadWait(1);
    }
    SND_PlayBGM(0x67, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
    state      = D_801F294C;
    D_801F294D = 0;
    D_801F294C = state + 1;
}
#else
INCLUDE_ASM(func_801D50E4);
#endif

MATCH void func_801D5194(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event2Step1Funcs, D_801F294D);
}

INCLUDE_ASM(func_801D51D0);

MATCH void func_801D5788(void) {
    POLY_G4* g4;
    TILE*    tile;
    s32      c;
    s32      d;
    s32      t;
    s32      n;

    func_801D5B2C();
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_SUB, 0x140, 0), 0);
    GFX_AddPrim(GFX_LAYER_TOP, sizeof(DR_MODE));
    g4 = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(g4);
    SetSemiTrans(g4, 1);
    d      = 0x140;
    c      = D_801DB0C4;
    g4->x0 = 0;
    g4->x1 = d;
    g4->x2 = 0;
    g4->x3 = d;
    setRGB0(g4, 0, 0, 0);
    setRGB1(g4, 0, 0, 0);
    setRGB2(g4, 0xFF, 0xFF, 0xFF);
    setRGB3(g4, 0xFF, 0xFF, 0xFF);
    g4->y0 = c;
    g4->y1 = c;
    c += 0x10;
    g4->y2 = c;
    g4->y3 = c;
    GFX_AddPrim(GFX_LAYER_TOP, sizeof(POLY_G4));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    t        = D_801DB0C4;
    tile->x0 = 0;
    tile->w  = d;
    setRGB0(tile, 0, 0, 0);
    tile->y0 = t + 0x10;
    tile->h  = 0xE0 - t;
    GFX_AddPrim(GFX_LAYER_TOP, sizeof(TILE));
    n          = D_801DB0C4;
    D_801DB0C4 = n + 1;
    if (g_InputHeld != 0) {
        D_801DB0C4 = n + 3;
    }
    if (D_801DB0C4 >= 0xC8) {
        D_801F294D += 1;
    }
}

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
        MESSAGE_START_WAIT(MSG_226);
        D_801F294D = 0;
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

    if (*state != GAME_REQUEST_MESSAGE) {
        Message_StartAreaMessage(MSG_238);
        *state = GAME_REQUEST_MESSAGE;
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
        if (pressed & PADLleft) {
            D_801DB0B4 -= 1;
            if ((s8)D_801DB0B4 < 0) {
                D_801DB0B4 = Fairy_CountFairies() - 1;
            }
        } else if (pressed & PADLright) {
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
    MESSAGE_START_WAIT(MSG_243);
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

MATCH void func_801D6634(void) {
    s32 i;
    u8* dst;
    u8(*tbl)[5];
    s32 letter;

    func_801D830C(0x44, 0x32, Fairy_FindActiveJob(D_801DB0B4), 0);
    func_801D97C8(D_801DAAA8, D_801DB0C4 * 30 + 0xB0, 0x2B);
    func_801D9B80(0x12, D_801DB0C4 * 30 + 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, D_801DB0C4 * 30 + 0x67, D_801DB0D4, D_801DB0D8);
    D_801DB0C4 -= 1;
    if (D_801DB0C4 == 0) {
        tbl = D_801457E8;
        dst = D_801DB080;
        for (i = 0; i < 5; i++, dst++) {
            letter = tbl[Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK][i];
            if (letter == 0) {
                letter = 0xFF;
            } else {
                letter = tbl[Fairy_FindActiveJob(D_801DB0B4) & BYTE_MASK][i];
            }
            *dst = letter;
        }
        D_801DB0D0 = 0;
        D_801DB0D4 = 0;
        D_801DB0D8 = 0;
        D_801DAAA8 = 2;
        D_801F294E += 1;
    }
}

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
            MESSAGE_START_WAIT(MSG_244);
            D_801F294E += 1;
        } else {
            MESSAGE_START_WAIT(MSG_247);
            D_801F294C = 4;
            D_801F294D = 0;
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
        MESSAGE_START_WAIT(MSG_247);
        D_801F294C = 4;
        D_801F294D = 0;
    }
}

MATCH void func_801D6CDC(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3Step2Funcs, D_801F294D);
}

MATCH void func_801D6D18(void) {
    s32 drawn;
    u32 i;
    u8  step;

    drawn      = 0;
    step       = D_801DB0C4 - 1;
    D_801DB0C4 = step;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x10 - step * 8) & 0xFFF8, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    for (i = 0; i < 7; i++) {
        if (g_Characters[i].party_flags & PARTY_FLAG_JOINED) {
            if ((drawn & 1) == 0) {
                func_801D90D8(0x20 - D_801DB0C4 * 40, (((u8)drawn >> 1) * 0x38) + 0x2B, (u8)i, 0);
            } else {
                func_801D90D8(D_801DB0C4 * 40 + 0xA8, (((u8)drawn >> 1) * 0x38) + 0x2B, (u8)i, 0);
            }
            drawn++;
        }
    }
    if (D_801DB0C4 == 0) {
        D_801F294D += 1;
    }
}

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

#ifdef NON_MATCHING
NON_MATCHING void func_801D7234(void) {
    s32 drawn;
    u32 i;
    u8  step;
    u8  drawn_index;
    s32 remaining;
    s32 x;
    s32 y;

    drawn      = 0;
    step       = D_801DB0C4 + 1;
    D_801DB0C4 = step;
    Menu_DrawHeaderBar(20, (0x10 - step * 8) & 0xFFF8, 280, 19, g_WindowStyle);
    for (i = 0; i < 7; i++) {
        if (g_Characters[i].party_flags & PARTY_FLAG_JOINED) {
            drawn_index = drawn;
            if (drawn_index == (s8)D_801DB0B4) {
                remaining = 4 - D_801DB0C4;
                x         = ((s8)D_801DB0B4 * 34 * remaining) + 32;
                y         = ((drawn_index >> 1) * 14) & 0xFF;
                y         = (y * remaining) + 43;
                func_801D90D8((s16)x, (s16)y, (u8)i, 0);
            } else if ((drawn & 1) == 0) {
                func_801D90D8(32 - D_801DB0C4 * 40, ((drawn_index >> 1) * 56) + 43, (u8)i, 0);
            } else {
                func_801D90D8(D_801DB0C4 * 40 + 168, ((drawn_index >> 1) * 56) + 43, (u8)i, 0);
            }
            drawn++;
        }
    }
    if (D_801DB0C4 == 4) {
        D_801DB0C4 = 4;
        D_801F294D = 7;
    }
}
#else
INCLUDE_ASM(func_801D7234);
#endif

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
    func_801D90D8(0x20, 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 0);
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
    MESSAGE_START_WAIT(MSG_243);
    D_801F294E++;
    func_801D90D8(0x20, 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 0);
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
    func_801D90D8(0x20, 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 0);
}

MATCH void func_801D75DC(void) {
    D_801DB0C4 = D_801DB0C4 + 1;
    func_801D90D8(0x20 - ((u8)D_801DB0C4 * 0x28), 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 0);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA7A4();
    }
}

MATCH void func_801D7660(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event3Step2Sub7Funcs, D_801F294E);
}

MATCH void func_801D769C(void) {
    s32        i;
    u8*        dst;
    Character* chars;
    s32        letter;

    D_801DB0C4 -= 1;
    func_801D90D8(0x20, 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 0);
    func_801D97C8(D_801DAAA8, D_801DB0C4 * 30 + 0xB0, 0x2B);
    func_801D9B80(0x12, D_801DB0C4 * 30 + 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, D_801DB0C4 * 30 + 0x67, D_801DB0D4, D_801DB0D8);
    if (D_801DB0C4 == 0) {
        chars = g_Characters;
        dst   = D_801DB080;
        for (i = 0; i < 5; i++, dst++) {
            letter = chars[Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK].name[i];
            if (letter == 0) {
                letter = 0xFF;
            } else {
                letter = chars[Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK].name[i];
            }
            *dst = letter;
        }
        D_801DB0D0 = 0;
        D_801DB0D4 = 0;
        D_801DB0D8 = 0;
        D_801DAAA8 = 2;
        D_801F294E += 1;
    }
}

MATCH void func_801D7878(void) {
    func_801D90D8(0x20, 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 1);
    func_801AE214((D_801DB0D0 * 8) + 0x5B, 0x50, 8, 0);
    func_801D97C8(D_801DAAA8, 0xB0, 0x2B);
    func_801D9B80(0x12, 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, 0x67, D_801DB0D4, D_801DB0D8);
    D_801DB0DC = func_801DA114();
}

MATCH void func_801D7934(void) {
    s32 i;

    D_801DB0C4 = D_801DB0C4 + 1;
    if (D_801DB0DC != 0) {
        func_801D90D8(0x20, 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 1);
    } else {
        func_801D90D8(0x20 - (D_801DB0C4 * 0x1E), 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 1);
    }
    func_801D97C8(D_801DAAA8, (D_801DB0C4 * 0x1E) + 0xB0, 0x2B);
    func_801D9B80(0x12, (D_801DB0C4 * 0x1E) + 0x61, 0x24, 0x11);
    func_801D94D0(D_801DAAA8, 0x18, (D_801DB0C4 * 0x1E) + 0x67, D_801DB0D4, D_801DB0D8);
    if (D_801DB0C4 == 4) {
        if (D_801DB0DC != 0) {
            if (D_801DB080[0] == 0) {
                for (i = 0; i < 5; i++) {
                    D_801DB080[i] = D_801DB058[Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK][i];
                }
            }
            MESSAGE_START_WAIT(MSG_244);
            D_801F294E += 1;
        } else {
            MESSAGE_START_WAIT(MSG_247);
            D_801F294C = 4;
            D_801F294D = 0;
        }
    }
}

MATCH void func_801D7B50(void) {
    func_801D90D8(0x20, 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 1);
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
    func_801D90D8(0x20 - ((u8)D_801DB0C4 * 0x1E), 0x2B, Party_GetJoinedCharacter(D_801DB0B4) & BYTE_MASK, 1);
    if ((u8)D_801DB0C4 == 4) {
        func_801DA7A4();
    }
}

MATCH void func_801D7C6C(void) {
    s32 drawn;
    u32 i;
    u8  step;

    drawn      = 0;
    step       = D_801DB0C4 + 1;
    D_801DB0C4 = step;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x10 - step * 8) & 0xFFF8, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    for (i = 0; i < 7; i++) {
        if (g_Characters[i].party_flags & PARTY_FLAG_JOINED) {
            if ((drawn & 1) == 0) {
                func_801D90D8(0x18 - D_801DB0C4 * 40, (((u8)drawn >> 1) * 0x38) + 0x30, (u8)i, 0);
            } else {
                func_801D90D8(D_801DB0C4 * 40 + 0xA8, (((u8)drawn >> 1) * 0x38) + 0x30, (u8)i, 0);
            }
            drawn++;
        }
    }
    if (D_801DB0C4 == 4) {
        MESSAGE_START_WAIT(MSG_247);
        D_801F294C = 4;
        D_801F294D = 0;
    }
}

/* func_801D7DD4 */
MATCH void Menu_StartFairyEndMessage(void) {
    u8* state = &g_GameStateIndex;

    if (*state != GAME_REQUEST_MESSAGE && D_801F294D == 0) {
        Message_StartAreaMessage(MSG_246);
        *state = GAME_REQUEST_MESSAGE;
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
    for (i = 0; i < FAIRY_JOB_COUNT; i++) {
        if (g_FairyJobs[i].active != 0) {
            if ((active_count & BYTE_MASK) == arg) {
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

#ifdef NON_MATCHING
NON_MATCHING void func_801D8058(s32 left, s32 top) {
    s32 i;
    s32 count;
    s32 x;
    s32 base_x;
    s32 y_fixed;

    x      = left;
    base_x = x;
    UI_DrawWindow(x, top, 172, 26, 0x80, g_WindowStyle);
    func_801D7EF0((s16)x, (s16)top);
    count = Fairy_CountFairies() & BYTE_MASK;
    if (count > 0) {
        y_fixed = (top + 9) << 16;
        x       = 7;
        i       = 0;
        while (i < count) {
            func_801D875C((s16)(base_x + x), (s16)(y_fixed >> 16), 1);
            i++;
            x += 8;
        }
    }
}
#else
INCLUDE_ASM(func_801D8058);
#endif

MATCH void func_801D812C(void) {
    u16 index;

    Menu_DrawHeaderBar(MENU_HEADER_X, 0x10, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    index = D_801DB0C8;
    if (index != 0xFFFF) {
        UI_DrawText(0x1B, 0x13, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, index));
    }
}

MATCH void func_801D81A4(s16 x, s16 y) {
    s32 i;
    s32 offset;

    COMMU_DRAW_CELL_GRID(func_801D875C, 0x22, 7, 4, 6);
}

INCLUDE_ASM(func_801D830C);

INCLUDE_ASM(func_801D851C);

MATCH void func_801D875C(s16 x, s16 y, s32 index) {
    s32   tpage;
    SPRT* sprt;
    u8    slot;

    slot = index;
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x2E;
    } else {
        tpage = 0x1E;
    }
    GFX_ADD_DRAW_MODE(tpage);
    sprt = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprt);
    sprt->x0   = x;
    sprt->y0   = y;
    sprt->u0   = D_801DAE88[slot][0];
    sprt->v0   = D_801DAE88[slot][1];
    sprt->w    = D_801DAE88[slot][2];
    sprt->h    = D_801DAE88[slot][3];
    sprt->clut = ((D_801DAE88[slot][5] + 0x1E0) << 6) | (D_801DAE88[slot][4] >> 4);
    sprt->r0   = 0x80;
    sprt->g0   = 0x80;
    sprt->b0   = 0x80;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}

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

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style) {
    s32 stack_18;
    u8  early;
    s32 stack_20;
    s32 stack_28;
    s32 stack_30;
    u16 stack_38;
    s32 stack_40;
    s32 stack_48;
    s32 tmp0;
    s32 val0;
    s32 val1;
    s8  tmp1;
    u16 tmp2;
    u16 tmp3;
    u16 tmp4;
    u16 tmp5;
    u16 tmp6;
    u16 val2;
    u16 val3;
    u16 val4;
    u16 val5;
    u16 val6;
    u8* val7;
    u8  tmp7;
    u8  val8;

    val7                   = g_GfxPrimCursor;
    val8                   = window_style;
    early                  = window_style;
    stack_18               = x;
    stack_20               = y;
    stack_28               = width;
    stack_30               = height;
    g_GfxPrimCursor        = val7 + 8;
    FIELD(s16, val7, 0x2u) = 0xF0;
    *(s16*)(val7)          = 0;
    FIELD(s16, val7, 0x4u) = 0x10;
    FIELD(s16, val7, 0x6u) = 0x10;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    val3 = (u16)stack_18;
    val6 = (u16)stack_20;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, 0xF, (RECT*)val7);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    val7 = g_GfxPrimCursor;
    SetPolyFT4((POLY_FT4*)val7);
    SetSemiTrans(val7, 1);
    val1                    = (val8 << 5) + 0x10;
    FIELD(u16, val7, 0x8u)  = val3;
    FIELD(u16, val7, 0xAu)  = val6;
    FIELD(u16, val7, 0x12u) = val6;
    FIELD(u16, val7, 0x18u) = val3;
    val2                    = stack_18 + 2;
    FIELD(u16, val7, 0x10u) = val2;
    val0                    = 0xAC;
    FIELD(u16, val7, 0x20u) = val2;
    FIELD(s8, val7, 0xCu)   = 0;
    FIELD(u8, val7, 0xDu)   = 0U;
    FIELD(u8, val7, 0x15u)  = 0U;
    FIELD(s8, val7, 0x1Cu)  = 0;
    FIELD(s16, val7, 0x4u)  = 0xAC;
    FIELD(s8, val7, 0x5u)   = 0xAC;
    FIELD(s16, val7, 0x6u)  = 0xAC;
    tmp7                    = stack_30 + 1;
    val4                    = stack_20 + tmp7;
    val8                    = tmp7;
    FIELD(u16, val7, 0x1Au) = val4;
    FIELD(u16, val7, 0x22u) = val4;
    FIELD(s8, val7, 0x14u)  = 2;
    FIELD(u8, val7, 0x1Du)  = val8;
    FIELD(s8, val7, 0x24u)  = 2;
    FIELD(u8, val7, 0x25u)  = val8;
    FIELD(u16, val7, 0xAu)  = (u16)(FIELD(u16, val7, 0xAu) + 2);
    FIELD(u16, val7, 0x1Au) = (u16)(FIELD(u16, val7, 0x1Au) - 3);
    FIELD(u8, val7, 0xDu)   = (u8)(FIELD(u8, val7, 0xDu) + 2);
    FIELD(u8, val7, 0x1Du)  = (u8)(FIELD(u8, val7, 0x1Du) - 3);
    FIELD(u16, val7, 0xEu)  = GetClut(val1, STAGE_PALETTE_Y + 1);
    stack_40                = stack_28 + 1;
    val3                    = (u16)stack_40;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    FIELD(s16, val7, 0x16u) = 0xF;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    val3     = (u16)((s32)((val3 & HALF_MASK) - 4) >> 1);
    val7     = g_GfxPrimCursor;
    stack_48 = (stack_28 - 3) & 1;
    SetPolyFT4((POLY_FT4*)val7);
    SetSemiTrans(val7, 1);
    tmp3                    = val3 + val2;
    val5                    = val3;
    FIELD(u16, val7, 0x8u)  = val2;
    FIELD(u16, val7, 0xAu)  = val6;
    FIELD(u16, val7, 0x10u) = tmp3;
    FIELD(u16, val7, 0x12u) = val6;
    FIELD(u16, val7, 0x18u) = val2;
    FIELD(u16, val7, 0x1Au) = val4;
    FIELD(u16, val7, 0x20u) = tmp3;
    FIELD(u16, val7, 0x22u) = val4;
    FIELD(s8, val7, 0xCu)   = 0;
    FIELD(u8, val7, 0xDu)   = 0U;
    FIELD(s8, val7, 0x14u)  = (s8)val5;
    FIELD(u8, val7, 0x15u)  = 0U;
    FIELD(s8, val7, 0x1Cu)  = 0;
    FIELD(u8, val7, 0x1Du)  = val8;
    FIELD(s8, val7, 0x24u)  = (s8)val5;
    FIELD(u8, val7, 0x25u)  = val8;
    FIELD(s16, val7, 0x4u)  = 0xAC;
    FIELD(s8, val7, 0x5u)   = 0xAC;
    FIELD(s16, val7, 0x6u)  = 0xAC;
    FIELD(u16, val7, 0xEu)  = GetClut(val1, STAGE_PALETTE_Y + 1);
    stack_38                = (u16)stack_48;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    FIELD(s16, val7, 0x16u) = 0xF;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    val7 = g_GfxPrimCursor;
    SetPolyFT4((POLY_FT4*)val7);
    SetSemiTrans(val7, 1);
    FIELD(u16, val7, 0xAu)  = val6;
    tmp0                    = stack_18 + val3;
    tmp2                    = tmp0 + 2;
    FIELD(u16, val7, 0x8u)  = tmp2;
    tmp5                    = tmp0 + (val3 + stack_48 + 2);
    FIELD(u16, val7, 0x10u) = tmp5;
    FIELD(u16, val7, 0x12u) = val6;
    FIELD(u16, val7, 0x18u) = tmp2;
    FIELD(u16, val7, 0x1Au) = val4;
    FIELD(u16, val7, 0x20u) = tmp5;
    FIELD(u16, val7, 0x22u) = val4;
    FIELD(s8, val7, 0xCu)   = 0;
    FIELD(u8, val7, 0xDu)   = 0U;
    tmp1                    = val5 + stack_38;
    FIELD(s8, val7, 0x14u)  = tmp1;
    FIELD(u8, val7, 0x15u)  = 0U;
    FIELD(s8, val7, 0x1Cu)  = 0;
    FIELD(u8, val7, 0x1Du)  = val8;
    FIELD(s8, val7, 0x24u)  = tmp1;
    FIELD(u8, val7, 0x25u)  = val8;
    FIELD(s16, val7, 0x4u)  = 0xAC;
    FIELD(s8, val7, 0x5u)   = 0xAC;
    FIELD(s16, val7, 0x6u)  = 0xAC;
    FIELD(u16, val7, 0xEu)  = GetClut(val1, STAGE_PALETTE_Y + 1);
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    FIELD(s16, val7, 0x16u) = 0xF;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    val7 = g_GfxPrimCursor;
    SetPolyFT4((POLY_FT4*)val7);
    SetSemiTrans(val7, 1);
    tmp4                    = stack_18 + stack_40;
    FIELD(u16, val7, 0x1Au) = val4;
    tmp6                    = tmp4 - 2;
    FIELD(u8, val7, 0x1Du)  = val8;
    FIELD(u16, val7, 0x10u) = tmp4;
    FIELD(u16, val7, 0x12u) = val6;
    FIELD(u16, val7, 0x20u) = tmp4;
    FIELD(u16, val7, 0x8u)  = tmp6;
    FIELD(u16, val7, 0x18u) = tmp6;
    FIELD(u16, val7, 0x22u) = val4;
    FIELD(u16, val7, 0xAu)  = val6;
    FIELD(s8, val7, 0xCu)   = 0;
    FIELD(u8, val7, 0xDu)   = 0U;
    FIELD(s8, val7, 0x14u)  = 2;
    FIELD(u8, val7, 0x15u)  = 0U;
    FIELD(s8, val7, 0x1Cu)  = 0;
    FIELD(s8, val7, 0x24u)  = 2;
    FIELD(u8, val7, 0x25u)  = val8;
    FIELD(s16, val7, 0x4u)  = 0xAC;
    FIELD(s8, val7, 0x5u)   = 0xAC;
    FIELD(s16, val7, 0x6u)  = 0xAC;
    FIELD(u16, val7, 0x12u) = (u16)(FIELD(u16, val7, 0x12u) + 2);
    FIELD(u16, val7, 0x22u) = (u16)(FIELD(u16, val7, 0x22u) - 3);
    FIELD(u16, val7, 0x1Au) = (u16)(FIELD(u16, val7, 0x1Au) - 1);
    FIELD(u8, val7, 0x15u)  = (u8)(FIELD(u8, val7, 0x15u) + 2);
    FIELD(u8, val7, 0x1Du)  = (u8)(FIELD(u8, val7, 0x1Du) - 1);
    FIELD(u8, val7, 0x25u)  = (u8)(FIELD(u8, val7, 0x25u) - 3);
    FIELD(u16, val7, 0xEu)  = GetClut(val1, STAGE_PALETTE_Y + 1);
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    FIELD(s16, val7, 0x16u) = 0xF;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    val7                   = g_GfxPrimCursor;
    g_GfxPrimCursor        = val7 + 8;
    *(s16*)(val7)          = 0;
    FIELD(s16, val7, 0x2u) = 0;
    FIELD(s16, val7, 0x4u) = 0x100;
    FIELD(s16, val7, 0x6u) = 0x100;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, 0xF, (RECT*)val7);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    func_801AEBA0((s16)val2, (s16)(stack_20 + 2), (s16)(stack_28 - 4), (s16)(stack_30 - 4), 0);
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif

#include "shared/Menu_DrawPortrait.h"

INCLUDE_ASM(func_801D90D8);

MATCH void func_801D9210(void) {
    s32 drawn;
    u32 i;

    drawn = 0;
    for (i = 0; i < 7; i++) {
        if (g_Characters[i].party_flags & PARTY_FLAG_JOINED) {
            func_801D90D8(((drawn & 1) * 0x88) + 0x20, (((u8)drawn >> 1) * 0x38) + 0x2B, (u8)i, 0);
            drawn++;
        }
    }
}

MATCH u8 func_801D92B0(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (g_Characters[i].party_flags & PARTY_FLAG_JOINED) {
            count++;
        }
    }
    return count;
}

MATCH u8 Party_GetJoinedCharacter(u8 arg) {
    s32 active_count;
    s32 i;

    active_count = 0;
    for (i = 0; i < 7; i++) {
        if (g_Characters[i].party_flags & PARTY_FLAG_JOINED) {
            if ((active_count & BYTE_MASK) == arg) {
                return (u8)i;
            }
            active_count++;
        }
    }
    return 0xFF;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801D9348(s32 x, s32 y, s32 color, s32 frame_mode) {
    u8       rgb[3];
    u8       base;
    u8       i;
    s32      width_copy;
    s32      bit;
    s32      state;
    s32      mask;
    LINE_F3* line3;
    LINE_F4* line4;

    width_copy = 0x7F;

    if ((u8)color != 0) {
        state = g_FrameCount;
        if (state & 8) {
            base = (u8)((state & 6) << 5 | 0x3F);
        } else {
            base = (u8)((~state & 6) << 5 | 0x3F);
        }
    } else {
        base = 0xFF;
    }

    mask = (u8)frame_mode;
    for (bit = 1, i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++, bit <<= 1) {
        if (bit & mask) {
            rgb[i] = base;
        } else {
            rgb[i] = 0;
        }
    }

    x += 2;
    line3 = (LINE_F3*)g_GfxPrimCursor;
    SetLineF3(line3);
    setXY3(line3, x + 4, y, x, y + 4, x, y + 0x34);
    setRGB0(line3, rgb[2], rgb[1], rgb[0]);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F3));

    line4 = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line4);
    setXY0(line4, x + 4, y);
    line4->x3 = x;
    line4->y3 = y + 0x34;
    line4->y1 = y;
    line4->y2 = y + 0x34;
    line4->x1 = (line4->x2 = x + width_copy - 1);
    setRGB0(line4, rgb[2], rgb[1], rgb[0]);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F4));
}
#else
INCLUDE_ASM(func_801D9348);
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801D94D0(s32 page, s32 left, s32 top, s32 cursor_col_arg, s32 cursor_row_arg) {
    u8  tags[20];
    u8* cell;
    u16 x;
    u16 y;
    u16 row;
    u16 col;
    u16 cursor_x;
    u16 cursor_y;
    u8  cursor_col;
    u8  cursor_row;
    u8  code;

    /* FAKE: retail reserves eight bytes outside the active locals. */
    FAKE_STACK_PADS(u8, 8);
    memcpy(tags, D_801D0C3C, 20);
    UI_DrawWindow(left, top, 0x110, 123, 0, g_WindowStyle);
    cell = D_801DAAAC + ((u8)page * 96);
    y    = top + 6;
    for (row = 0; row < 8; row++) {
        x = left + 4;
        for (col = 0; col < 12; col++) {
            if (col == 10 && row >= 3) {
                code = *cell;
                switch (code) {
                    case 1:
                        UI_DrawText((s16)x, (s16)y, 4, 5, tags);
                        break;
                    case 2:
                        UI_DrawText((s16)x, (s16)y, 4, 5, tags + 5);
                        break;
                    case 3:
                        UI_DrawText((s16)x, (s16)y, 2, 5, tags + 10);
                        break;
                    case 4:
                        UI_DrawText((s16)x, (s16)y, 2, 5, tags + 15);
                        break;
                    default:
                        UI_DrawText((s16)x, (s16)y, 0, 1, cell);
                        break;
                }
            } else {
                UI_DrawText((s16)x, (s16)y, 0, 1, cell);
            }
            x += (col == 4 || col == 9) ? 28 : 20;
            cell++;
        }
        y += 14;
    }
    cursor_col = cursor_col_arg;
    cursor_row = cursor_row_arg;
    cursor_x   = left + 6 + cursor_col * 20;
    if (cursor_col >= 5) {
        cursor_x += 8;
    }
    if (cursor_col >= 10) {
        cursor_x += 8;
    }
    if (cursor_col == 11 && cursor_row >= 3) {
        cursor_x -= 20;
    }
    cursor_y = top + 8 + cursor_row * 14;
    Menu_DrawCursorSprite(cursor_x, cursor_y, 0);
}
#else
INCLUDE_ASM(func_801D94D0);
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801D97C8(s32 unused, s32 x, s32 y) {
    const u8* const* labels;
    const u8*        dots;
    u16              row;
    u16              column;
    u16              clut;
    s32              tpage;
    s32              left;

    left = x;
    UI_DrawWindow((u16)(x + 3), (u16)(y + 3), 0x4D, 0x2F, 0, g_WindowStyle);
    labels = D_801DB038;
    for (row = 0; row < 5; row++) {
        UI_DrawTextString((s16)(x + 0x2A), (s16)(y + (row * 8) + 6), 0, 0x10, labels[row]);
    }
    for (row = 0; row < 5; row++) {
        for (column = 0; column < 3; column++) {
            dots = D_801DB054;
            UI_DrawTextString((s16)(left + (column * 4) + 0x1A), (s16)(y + (row * 8) + 6), 0, 1, dots);
        }
    }

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x8F;
    } else {
        tpage = 0x2F;
    }
    GFX_ADD_DRAW_MODE(tpage);

    clut = GetClut(0x30, 0x1E0);
    Menu_DrawPanelIcon((s16)(left + 0x0E), (s16)(y + 6), 0x1D, 0, clut, 0x7F);
    clut = GetClut(0x30, 0x1E0);
    Menu_DrawPanelIcon((s16)(left + 0x0E), (s16)(y + 0x0E), 0x1C, 0, clut, 0x7F);
    clut = GetClut(0x30, 0x1E0);
    Menu_DrawPanelIcon((s16)(left + 0x0E), (s16)(y + 0x16), 0x1B, 0, clut, 0x7F);
    clut = GetClut(0x30, 0x1E0);
    Menu_DrawPanelIcon((s16)(left + 0x0E), (s16)(y + 0x1E), 0x1E, 0, clut, 0x7F);
    clut = GetClut(0, 0x1E0);
    Menu_DrawPanelIcon((s16)(left + 0x0A), (s16)(y + 0x26), 4, 2, clut, 0x7F);
    clut = GetClut(0, 0x1E0);
    Menu_DrawPanelIcon((s16)(left + 0x12), (s16)(y + 0x26), 5, 2, clut, 0x7F);
    func_801AF390((s16)left, (s16)y, g_MenuPortraitAtlas + 0xC8, 0);
}
#else
INCLUDE_ASM(func_801D97C8);
#endif

MATCH void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801D9B80(s32 x, s32 y, s32 width, s32 height) {
    RECT  window;
    SPRT* sprite;
    s32   columns;
    s32   rows;
    s32   edge;

    window.x = 112;
    window.y = 152;
    window.w = 8;
    window.h = 8;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 832, 256), &window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x + 16, y);
    setUV0(sprite, 0, 0);
    edge = 8;
    setWH(sprite, ((u8)width - 4) * 8, edge);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));

    window.x = 152;
    window.y = 160;
    window.h = edge;
    window.w = edge;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 832, 256), &window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x + 16, y + ((u8)height - 1) * 8);
    setUV0(sprite, 0, 0);
    edge = 8;
    setWH(sprite, ((u8)width - 4) * 8, edge);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));

    window.x = 176;
    window.y = 152;
    window.h = edge;
    window.w = edge;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 832, 256), &window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x, y + 16);
    setUV0(sprite, 0, 0);
    edge = 8;
    setWH(sprite, edge, ((u8)height - 4) * 8);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));

    window.x = 176;
    window.y = 160;
    window.h = edge;
    window.w = edge;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 832, 256), &window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x + ((u8)width - 1) * 8, y + 16);
    setUV0(sprite, 0, 0);
    edge = 8;
    setWH(sprite, edge, ((u8)height - 4) * 8);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));

    window.x = 112;
    window.y = 160;
    window.h = edge;
    window.w = edge;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 832, 256), &window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setXY0(sprite, x + 8, y + 8);
    setUV0(sprite, 0, 0);
    setWH(sprite, ((u8)width - 2) * 8, ((u8)height - 2) * 8);
    setClut(sprite, 176, STAGE_PALETTE_Y + 1);
    setRGB0(sprite, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));

    window.x = 0;
    window.y = 0;
    window.w = 256;
    window.h = 256;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 832, 256), &window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    UI_DrawSprite((s16)x, (s16)y, 0x23, 1);
    columns = (u8)width - 2;
    UI_DrawSprite((s16)(x + columns * 8), (s16)y, 0x26, 1);
    rows = (u8)height - 2;
    UI_DrawSprite((s16)x, (s16)(y + rows * 8), 0x27, 1);
    UI_DrawSprite((s16)(x + columns * 8), (s16)(y + rows * 8), 0x29, 1);
}
#else
INCLUDE_ASM(func_801D9B80);
#endif

#ifdef NON_MATCHING
NON_MATCHING s8 func_801DA114(void) {
    s32 pressed;
    u8* page;
    u8* row;
    u8* cell;
    s32 col;
    s8  i;
    s32 count;
    u16 pad;

    pressed = INPUT_GetRepeatedButtons(g_InputPressed & 0xF00F);
    cell    = D_801DAAAC + D_801DAAA8 * 96 + (s8)D_801DB0D8 * 12 + (s8)D_801DB0D4;
    if (pressed & 0x1000) {
        SND_PlayCue(0x100);
        page = D_801DAAAC + D_801DAAA8 * 96;
        col  = (s8)D_801DB0D4;
        do {
            D_801DB0D8 -= 1;
            if ((s8)D_801DB0D8 < 0) {
                D_801DB0D8 = 7;
            }
        } while (page[(s8)D_801DB0D8 * 12 + col] == 0);
    } else if (pressed & 0x4000) {
        SND_PlayCue(0x100);
        page = D_801DAAAC + D_801DAAA8 * 96;
        col  = (s8)D_801DB0D4;
        do {
            D_801DB0D8 += 1;
            if ((s8)D_801DB0D8 >= 8) {
                D_801DB0D8 = 0;
            }
        } while (page[(s8)D_801DB0D8 * 12 + col] == 0);
    } else if (pressed & 0x8000) {
        SND_PlayCue(0x100);
        if (*cell != 0 && *cell < 6) {
            D_801DB0D4 = 9;
        } else {
            row = D_801DAAAC + D_801DAAA8 * 96 + (s8)D_801DB0D8 * 12;
            do {
                D_801DB0D4 -= 1;
                if ((s8)D_801DB0D4 < 0) {
                    D_801DB0D4 = 11;
                }
            } while (row[(s8)D_801DB0D4] == 0);
        }
    } else if (pressed & 0x2000) {
        SND_PlayCue(0x100);
        if (*cell != 0 && *cell < 6) {
            D_801DB0D4 = 0;
        } else {
            row = D_801DAAAC + D_801DAAA8 * 96 + (s8)D_801DB0D8 * 12;
            do {
                D_801DB0D4 += 1;
                if ((s8)D_801DB0D4 >= 12) {
                    D_801DB0D4 = 0;
                }
            } while (row[(s8)D_801DB0D4] == 0);
        }
    }

    pad = g_InputPressed;
    if (pad & 0x40) {
        cell = D_801DAAAC + D_801DAAA8 * 96 + (s8)D_801DB0D8 * 12 + (s8)D_801DB0D4;
        switch (*cell) {
            case 1:
                if (D_801DB0D0 < 4) {
                    SND_PlayCue(0x103);
                    D_801DB0D0 += 1;
                } else {
                    SND_PlayCue(0x107);
                }
                break;
            case 2:
                if (D_801DB0D0 != 0) {
                    SND_PlayCue(0x103);
                    D_801DB0D0 -= 1;
                } else {
                    SND_PlayCue(0x107);
                }
                break;
            case 3:
                D_801F294E += 1;
                return 0;
            case 4:
                g_InputPressed = pad | 0x800;
                break;
            default:
                SND_PlayCue(0x103);
                D_801DB080[D_801DB0D0] = *cell;
                if (D_801DB0D0 < 4) {
                    D_801DB0D0 += 1;
                }
                break;
        }
    }

    if ((g_InputPressed & 0x20) || (pressed & 0xA)) {
        if (D_801DB0D0 >= 4) {
            return 0;
        }
        SND_PlayCue(0x101);
        D_801DB0D0 += 1;
        return 0;
    }
    if ((g_InputPressed & 0x80) || (pressed & 0x4) || (pressed & 0x1)) {
        if (D_801DB0D0 == 0) {
            return 0;
        }
        SND_PlayCue(0x101);
        D_801DB0D0 -= 1;
        return 0;
    }
    if (g_InputPressed & 0x10) {
        u8 slot = D_801DB0D0;

        if (slot != 0 && (D_801DB080[slot] == 0xFF || D_801DB080[slot] == 0)) {
            D_801DB0D0 = slot - 1;
        }
        SND_PlayCue(0x106);
        D_801DB080[D_801DB0D0] = 0xFF;
        return 0;
    }
    if (g_InputPressed & 0x800) {
        SND_PlayCue(0x104);
        count = 5;
        for (i = 4; i >= 0 && D_801DB080[i] == 0xFF; i--) {
            count -= 1;
        }
        if ((u16)count < 5) {
            for (i = 4; i >= 0 && D_801DB080[i] == 0xFF; i--) {
                D_801DB080[i] = 0;
            }
        }
        D_801F294E += 1;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801DA114);
#endif

MATCH void func_801DA7A4(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        g_TextVariables[0][i] = g_Characters[Party_GetJoinedCharacter(D_801DB0B4)].name[i];
    }
    D_801490DD = 0;
    for (i = 0; i < 6; i++) {
        D_801490F8[i] = D_801DB080[i];
    }
    for (i = 0; i < 5; i++) {
        g_Characters[Party_GetJoinedCharacter(D_801DB0B4)].name[i] = D_801DB080[i];
    }
    MESSAGE_START_WAIT(MSG_245);
    D_801F294C = 3;
    D_801F294D = 0;
    D_801F294E = 0;
}

MATCH void func_801DA8E8(void) {
    s32 i;
    u8  started;
    u8* src;
    u8(*jobs)[5];

    started = 0;
    for (i = 4; i >= 0; i--) {
        if (D_801457E8[Fairy_FindActiveJob(D_801DB0B4)][i] == 0xFF && started == 0) {
            g_TextVariables[0][i] = 0;
        } else {
            started               = 1;
            g_TextVariables[0][i] = D_801457E8[Fairy_FindActiveJob(D_801DB0B4)][i];
        }
    }
    D_801490DD = 0;
    for (i = 0; i < 6; i++) {
        D_801490F8[i] = D_801DB080[i];
    }
    i    = 0;
    jobs = D_801457E8;
    src  = D_801DB080;
    for (; i < 5; i++, src++) {
        if (*src == 0) {
            jobs[Fairy_FindActiveJob(D_801DB0B4)][i] = 0xFF;
        } else {
            jobs[Fairy_FindActiveJob(D_801DB0B4)][i] = *src;
        }
    }
    MESSAGE_START_WAIT(MSG_245);
    D_801F294C = 3;
    D_801F294D = 0;
    D_801F294E = 0;
}
