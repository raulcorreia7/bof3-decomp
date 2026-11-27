#include "area104_14.h"

/* Counts the timer down, changes area at zero and draws the seconds, tenths and a jittering last digit. */
MATCH void func_801F60C0(void) {
    s8 digit;

    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_GameFlags &= ~GAME_FLAG_MENU_LOCK;
        Actor_Clear();
    } else if (g_GameStateIndex == GAME_REQUEST_IDLE && g_Game.members[0].header.mode == 0xC) {
        if (SELF(Actor)->unk_0A == 0) {
            if (SELF(Actor)->timer == 0) {
                Game_RequestAreaChange(0x79, 0x190000, 0x2D0000, 7);
                g_GameFlags &= ~GAME_FLAG_MENU_LOCK;
                Actor_Clear();
                return;
            }
            SELF(Actor)->timer--;
            SELF(Actor)->unk_0A = 0x1D;
        } else {
            SELF(Actor)->unk_0A--;
        }
    }
    /* FAKE: the prototype takes u8, which zero-extends; retail calls without it and sign-extends. */
    ((void (*)())UI_WindowDraw)(0x7E, 0x2E, 0x48, 0x11, 0xF2, (s8)g_WindowStyle);
    UI_WindowDrawFrame(0x80, 0x30, 0x44, 0xD, 2);
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        digit = rand() & 3;
        digit = digit < 0 ? 0 : digit < 3 ? digit : 2;
    } else {
        digit = 0;
    }
    digit += (u8)(SELF(Actor)->unk_0A % 3) * 3;
    digit = digit < 0 ? 0 : digit < 10 ? digit : 9;
    sprintf(g_UITextFormatBuffer, D_801F2C08, SELF(Actor)->timer, (u8)(SELF(Actor)->unk_0A / 3), digit);
    g_UITextFormatBuffer[2] = 0x8F;
    if (SELF(Actor)->timer < 10 && (g_FrameCount & 4)) {
        UI_TextDrawAscii(0x8E, 0x30, 2, g_UITextFormatBuffer);
    } else {
        UI_TextDrawAscii(0x8E, 0x30, 0, g_UITextFormatBuffer);
    }
    func_801F6774();
    func_801F6368();
}
