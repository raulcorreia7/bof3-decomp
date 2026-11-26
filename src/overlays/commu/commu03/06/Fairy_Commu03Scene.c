#include "commu03_06.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

void func_801D1714(s16 x, s16 y, u32 clut, u8* text);

/* The commu03 overlay entry: the shared commu step byte selects the handler. */
MATCH void func_801D0C44(void) {
    SYS_DISPATCH_BYTE(g_Commu03Steps, D_801F294C);
}

MATCH void func_801D0C80(void) {
    SYS_DISPATCH_BYTE(g_Commu03Step0Steps, D_801F294D);
}

MATCH void func_801D0CBC(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 5; j++) {
            g_TextVariables[i][j] = g_Characters[i].name[j];
        }
        g_TextVariables[i][5] = 0;
    }
    D_801D1948 = 4;
    D_801D1940 = 0;
    D_801D1944 = g_SndBGMId;
    D_801F294D++;
}

MATCH void func_801D0D60(void) {
    u8 value;

    value      = D_801D1948 - 1;
    D_801D1948 = value;
    func_801D1250(0x32, (s16)(0x28 - ((value & BYTE_MASK) * 0x32)));
    if (D_801D1948 == 0) {
        D_801F294D = 0;
        D_801F294C += 1;
    }
}

MATCH void func_801D0DEC(void) {
    SYS_DISPATCH_BYTE(g_Commu03Step1Steps, D_801F294D);
}

MATCH void func_801D0E28(void) {
    volatile u16* pad;
    s32           index;
    s32           count;
    s32           bgm_offset;
    u16           buttons;
    u16           held;
    s16           cue;

    index   = g_SceneEventSelection;
    count   = D_801457AB[(g_FairyJobs[index].type - 1) << 3];
    pad     = &g_PadStates[0].pressed;
    buttons = INPUT_REPEATED(*pad, PADLleft | PADLright);
    if (buttons != 0) {
        if ((buttons & PADLright) != 0) {
            D_801D1940 = D_801D1940 + 1;
            if (count < (s16)D_801D1940) {
                D_801D1940 = 0;
            }
        } else if ((buttons & PADLleft) != 0) {
            D_801D1940 = D_801D1940 - 1;
            if ((s16)D_801D1940 < 0) {
                D_801D1940 = count;
            }
        }
        func_801D1250(0x32, 0x28);
    } else {
        held = *pad;
        if ((held & PADRdown) != 0) {
            if (g_SndBGMId != BGM_NONE) {
                bgm_offset = g_SndBGMId * 4;
                SND_SeqStop(*(g_SelectionSepSlots + bgm_offset), *(g_SelectionSequences + bgm_offset));
            }
            cue = D_801D1918[D_801D1940];
            if (g_SndBGMId == cue) {
                g_SndBGMId = BGM_NONE;
            } else {
                SND_BGMRequest(cue);
                D_801F294D += 1;
            }
        } else if ((held & PADRup) != 0) {
            D_801F294D = 0;
            D_801F294C += 1;
        }
        func_801D1250(0x32, 0x28);
    }
}

MATCH void func_801D1000(void) {
    if (EMI_IsReady()) {
        s16 idx = D_801D1940;
        u8  cue = D_801D1918[idx];
        SND_BGMPlay(cue, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
        D_801F294D = 0;
    }
    func_801D1250(0x32, 0x28);
}

MATCH void func_801D1058(void) {
    SYS_DISPATCH_BYTE(g_Commu03Step2Steps, D_801F294D);
}

MATCH void func_801D1094(void) {
    s32 bgm_offset;

    if (g_SndBGMId != BGM_NONE) {
        if (g_SndBGMId != D_801D1944) {
            bgm_offset = g_SndBGMId * 4;
            SND_SeqStop(*(g_SelectionSepSlots + bgm_offset), *(g_SelectionSequences + bgm_offset));
        }
    }
    SND_BGMRequest(D_801D1944);
    func_801D1250(0x32, 0x28);
    D_801F294D += 1;
}

MATCH void func_801D1124(void) {
    if (EMI_IsReady() != 0) {
        SND_BGMPlay(D_801D1944, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
        D_801D1948 = 0;
        D_801F294D += 1;
    }
    func_801D1250(0x32, 0x28);
}

MATCH void func_801D1184(void) {
    u8 count;

    count      = D_801D1948 + 1;
    D_801D1948 = count;
    func_801D1250(0x32, (s16)(0x28 - count * 0x32));
    if (D_801D1948 == 4) {
        MESSAGE_START_WAIT(MSG_AREA175_THANKS_COME_BACK);
        D_801F294D += 1;
    }
}

#include "overlays/commu/shared/Fairy_EndCommuScene.h"

#ifdef NON_MATCHING
/* Draws the fairy's leave-taking screen: the cue's text in the two windows, the
 * volume labels and the left and right volume bars. */
NON_MATCHING void func_801D1250(s32 scene, s32 mode) {
    s16       x;
    s16       y;
    s16       vol_l;
    s16       vol_r;
    s32       i;
    s32       sums[2];
    POLY_FT4* prim;
    s32       left;
    s32       top;
    s32       bar_x;

    x = scene;
    y = mode;
    /* Retail loads the style byte signed. */
    func_801AE3F0(x, y, 0xDC, 0x6E, 0xF0, *(s8*)&g_WindowStyle);
    func_801AED54(x + 4, y + 4, 0xD2, 0x66, 0);
    func_801AED54(x + 8, y + 8, 0xCA, 0x5E, 0);
    func_801AED54(x + 0x10, y + 0x12, 0xBC, 0x22, 1);

    left = scene;
    top  = mode;
    if (g_SndBGMId == D_801D1918[D_801D1940]) {
        UI_TextDraw((s16)(scene + 0x14), (s16)(mode + 0x17), 2, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, D_801D1940 + 0x271));
    } else {
        UI_TextDraw((s16)(scene + 0x14), (s16)(mode + 0x17), 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, D_801D1940 + 0x271));
    }

    func_801AE3F0((s16)left + 0x48, (s16)top + 0x3C, 0x7C, 0xE, 1, *(s8*)&g_WindowStyle);
    func_801AED54((s16)left + 0x48, (s16)top + 0x3C, 0x7C, 0xE, 1);

    if (g_SndMono == 0) {
        func_801D1714((s16)(left + 0x10), (s16)(top + 0x40), 0, D_801D1904);
    } else {
        func_801D1714((s16)(left + 0x10), (s16)(top + 0x40), 0, D_801D1908);
    }
    func_801D1714((s16)(left + 0x20), (s16)(top + 0x54), 0, D_801D190C);
    UI_TextDrawString((s16)(left + 0x44), (s16)(top + 0x54), 0, 3, D_801D18F4);
    UI_TextDrawString((s16)(left + 0x5C), (s16)(top + 0x54), 3, 1, D_801D18F8);
    UI_TextDrawString((s16)(left + 0x94), (s16)(top + 0x54), 0, 3, D_801D18F4);
    UI_TextDrawString((s16)(left + 0xAC), (s16)(top + 0x54), 3, 1, D_801D18FC);

    sums[0] = 0;
    sums[1] = 0;
    for (i = 0; i < 24; i++) {
        if (SpuGetKeyStatus(1 << i) != 0) {
            SpuGetVoiceVolume(i, &vol_l, &vol_r);
            sums[0] += (s16)(vol_l / 300);
            sums[1] += (s16)(vol_r / 300);
        }
    }
    sums[0] = sums[0] < 0 ? 0 : sums[0] >= 0x7B ? 0x7A : sums[0];
    sums[1] = sums[1] < 0 ? 0 : sums[1] >= 0x7B ? 0x7A : sums[1];

    for (i = 0; i < 2; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        bar_x    = left + 0x49;
        prim->x0 = bar_x;
        prim->x1 = bar_x + sums[i];
        prim->y1 = prim->y0 = top + 0x3F + i * 4;
        prim->u0            = 0x98;
        prim->u1            = 0x9C;
        prim->v1 = prim->v0 = 0xD8;
        prim->clut          = getClut(176, 480);
        prim->x2            = prim->x0;
        prim->y3 = prim->y2 = prim->y0 + 4;
        setRGB0(prim, 0x80, 0x80, 0x80);
        prim->u3 = prim->u1;
        prim->u2 = prim->u0;
        prim->x3 = prim->x1;
        prim->v3 = prim->v2 = prim->v0 + 8;
        prim->tpage         = getTPage(0, 0, 960, 0);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    }
}
#else
INCLUDE_ASM(func_801D1250);
#endif

#ifdef NON_MATCHING
/* Draws one 8x8 glyph quad per byte of the string, eight pixels apart, skipping
 * spaces. */
NON_MATCHING void func_801D1714(s16 x, s16 y, u32 clut, u8* text) {
    POLY_FT4* poly;
    s32       t1;
    s32       t2;
    u16       color;
    u8        c;
    u8        u;
    u8        v;

    color = (clut & 0x3F) | STAGE_PALETTE_CLUT;
    c     = *text;
    while (c != 0) {
        if (c != ' ') {
            poly = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(poly);
            poly->x0 = x + 4;
            poly->x1 = x + 0xC;
            poly->y1 = poly->y0 = y;
            poly->y3 = poly->y2 = poly->y0 + 8;
            poly->x2            = poly->x0 - 4;
            poly->x3            = poly->x1 - 4;
            u                   = ((*text - ' ') % 32) * 8;
            poly->u0            = u;
            poly->u1            = u + 7;
            poly->u2            = poly->u0;
            poly->u3            = poly->u1;
            poly->v1 = poly->v0 = ((*text - ' ') / 32) * 8;
            setRGB0(poly, 0x80, 0x80, 0x80);
            poly->clut = color;
            poly->v3 = poly->v2 = poly->v0 + 8;
            poly->tpage         = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
            GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
        }
        text += 1;
        x += 8;
        c = *text;
    }
}
#else
INCLUDE_ASM(func_801D1714);
#endif

MATCH void func_801D18AC(void) {
    u8* state;

    state = &g_SceneEventState.step;
    *state += 1;
}
