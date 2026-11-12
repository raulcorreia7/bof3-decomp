#include "game_00.h"

MATCH void func_801C5874(void) {
    u8*  base;
    s32* px;
    s32* py;
    s32* list;
    s32  target;
    u8   sel;
    s32  dx;
    s32  dy;
    s32  range;
    s32  step;

    base = &D_80143FBD;
    if (*base != 0) {
        *base -= 1;
        return;
    }
    list       = FIELD(s32*, g_AreaLoads[g_GameAreaId], 0x1Cu);
    target     = list[D_80143FBF];
    /* GameWork cell aliases the flag cluster at D_80143FBD - 0x75. */
    g_Task     = (Actor*)(base - 0x75);
    sel        = func_801A8D38(base - 1, target);
    D_80143F50 = sel;
    if (base[-1] & 0x8) {
        base[-1] &= 0xF7;
        D_80143F49 = 0;
        D_80143F4A = 0;
        D_80143F4B = 0;
        D_80143FC0 = 3;
        return;
    }
    if (sel == GAME_NONE) {
        if (base[-1] & 0x4) {
            px    = &g_AreaScrollTargetX;
            py    = &g_AreaScrollTargetY;
            dx    = *px - g_PartyX;
            dy    = *py - g_PartyY;
            range = ABS(dx);
            CLAMP_MIN(range, ABS(dy));
            if (range == 0) {
                base[-1] &= 0xFB;
                /* Shared tail: clears the movement state. */
                goto tail;
            }
            range *= 2;
            g_AreaCameraStep       = (g_RouteSpeedScale[D_80143FC0] * 8);
            step                   = (D_80143F84 - (Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY) << 16)) / ((0x80 / g_AreaCameraStep) * (range >> 16));
            g_AreaCameraHeightStep = 0;
            D_80143F4A             = 3;
            g_ScrollHeight         = g_AreaCameraHeight;
            *px                    = g_PartyX;
            *py                    = g_PartyY;
            D_80143F5C             = step;
            return;
        }
        g_AreaScrollTargetX = g_PartyX;
        g_AreaScrollTargetY = g_PartyY;
        func_80153DE8();
        D_80143F50 = 0;
    } else {
        if (base[-1] & 0x20) {
            D_80143F4A = 2;
            return;
        }
        if (base[-1] & 0x80) {
            D_80143F4A = 4;
            return;
        }
        if (D_80143FC3 != 0) {
            D_80143F84 += D_80143F5C;
            /* FAKE: barrier keeps argument load below the store. */
            FAKE_BARRIER();
            Area_AdvanceScroll(g_ScrollHeight);
            D_80143F4A = 1;
            return;
        }
    }
tail:
    D_80143F4A = 0;
}
