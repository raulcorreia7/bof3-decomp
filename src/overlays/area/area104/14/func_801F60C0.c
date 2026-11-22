#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F60C0(void) {
    s32 jitter;
    s32 roll;
    s8  digit;

    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_GameFlags &= ~GAME_FLAG_MENU_LOCK;
        Actor_Clear();
    } else if (g_GameStateIndex == GAME_REQUEST_IDLE && g_Game.members[0].header.mode == 0xC) {
        if (g_Task->unk_0A == 0) {
            if (g_Task->timer == 0) {
                Game_RequestAreaChange(0x79, 0x190000, 0x2D0000, 7);
                g_GameFlags &= ~GAME_FLAG_MENU_LOCK;
                Actor_Clear();
                return;
            }
            g_Task->timer--;
            g_Task->unk_0A = 0x1D;
        } else {
            g_Task->unk_0A--;
        }
    }
    UI_WindowDraw(0x7E, 0x2E, 0x48, 0x11, 0xF2, (s8)g_WindowStyle);
    UI_WindowDrawFrame(0x80, 0x30, 0x44, 0xD, 2);
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        roll   = rand() & 3;
        jitter = roll < 0 ? 0 : roll < 3 ? roll : 2;
    } else {
        jitter = 0;
    }
    digit = jitter + (u8)(g_Task->unk_0A % 3) * 3;
    digit = digit < 0 ? 0 : digit < 10 ? digit : 9;
    sprintf(g_UiTextFormatBuffer, D_801F2C08, g_Task->timer, (u8)(g_Task->unk_0A / 3), digit);
    g_UiTextFormatBuffer[2] = 0x8F;
    if (g_Task->timer < 10 && (g_FrameCount & 4)) {
        UI_TextDrawAscii(0x8E, 0x30, 2, g_UiTextFormatBuffer);
    } else {
        UI_TextDrawAscii(0x8E, 0x30, 0, g_UiTextFormatBuffer);
    }
    func_801F6774();
    func_801F6368();
}
#else
INCLUDE_ASM(func_801F60C0);
#endif
