#include "commu03_06.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

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
    pad     = &g_InputPressed;
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
                SND_StopSequence(*(g_SelectionCues + bgm_offset), *(g_SelectionSequences + bgm_offset));
            }
            cue = D_801D1918[D_801D1940];
            if (g_SndBGMId == cue) {
                g_SndBGMId = BGM_NONE;
            } else {
                SND_RequestBGM(cue);
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
        SND_PlayBGM(cue, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
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
            SND_StopSequence(*(g_SelectionCues + bgm_offset), *(g_SelectionSequences + bgm_offset));
        }
    }
    SND_RequestBGM(D_801D1944);
    func_801D1250(0x32, 0x28);
    D_801F294D += 1;
}

MATCH void func_801D1124(void) {
    if (EMI_IsReady() != 0) {
        SND_PlayBGM(D_801D1944, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
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
        MESSAGE_START_WAIT(MSG_090);
        D_801F294D += 1;
    }
}

#include "overlays/commu/Fairy_EndCommuScene.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D1250(s32 scene, s32 mode) {
    g_ScenarioState.step_05 = scene + mode;
}
#else
INCLUDE_ASM(func_801D1250);
#endif

#ifdef NON_MATCHING
/* Draws one 8x8 glyph quad per byte of the string, eight pixels apart, skipping
 * spaces. */
NON_MATCHING void func_801D1714(s16 x, s16 y, u32 clut, u8* text) {
    POLY_FT4* poly;
    u8*       p;
    s16       X;
    s16       Y;
    s32       t1;
    s32       t2;
    u16       color;
    u8        c;
    u8        u;
    u8        v;

    p     = text;
    X     = x;
    Y     = y;
    color = (clut & 0x3F) | STAGE_PALETTE_CLUT;
    c     = *p;
    while (c != 0) {
        if (c != ' ') {
            poly = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(poly);
            poly->x0 = X + 4;
            poly->x1 = X + 0xC;
            poly->y1 = poly->y0 = Y;
            poly->x2            = poly->x0 - 4;
            poly->y3 = poly->y2 = poly->y0 + 8;
            poly->x3            = poly->x1 - 4;
            c                   = *p;
            t1                  = c - ' ';
            if (t1 < 0) {
                t2 = c - 1;
            } else {
                t2 = t1;
            }
            u        = (t1 - ((t2 >> 5) << 5)) << 3;
            poly->u0 = u;
            poly->u1 = u + 7;
            poly->u2 = poly->u0;
            poly->u3 = poly->u1;
            c        = *p;
            t1       = c - ' ';
            if (t1 < 0) {
                t2 = c - 1;
            } else {
                t2 = t1;
            }
            v          = (t2 >> 5) << 3;
            poly->v0   = v;
            poly->v1   = poly->v0;
            poly->r0   = 0x80;
            poly->g0   = 0x80;
            poly->b0   = 0x80;
            poly->clut = color;
            poly->v3 = poly->v2 = poly->v1 + 8;
            poly->tpage         = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
            GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
        }
        p += 1;
        X += 8;
        c = *p;
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
