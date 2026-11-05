#include "game_00.h"

MATCH void func_801A83DC(void) {
    s8* state;

    state = &D_801448EC;
    switch (*state) {
        case 0: {
            u8* game_state;
            game_state = &g_GameStateIndex;

            if (*game_state != GAME_REQUEST_MESSAGE) {
                /* Dest is the bit buffer at 0x80145548 (ahead of the celerity and
                 * bonebreak timers); base+offset keeps the s0-reuse addiu, absolute form regresses
                 * bytes. */
                SYS_SetFlag(state + 0xC5C, D_801448ED);
                strncpy((char*)g_TextVariables[0], (char*)Resource_GetText((u32)(D_801448ED + 0x4172)), 8);
                D_801490E0 = 0;
                Resource_RequestArea(0xFA);
                *game_state = GAME_REQUEST_MESSAGE;
                if (g_SndBgmId != GAME_NONE) {
                    SND_PauseBgm(g_SndBgmId);
                }
                SND_StartXaStream(9, 1);
                *state = 1;
                return;
            }
            return;
        }
        case 1:
            if ((SND_IsXaIdle() & BYTE_MASK) && (g_GameStateIndex != GAME_REQUEST_MESSAGE)) {
                if (g_SndBgmId != GAME_NONE) {
                    SND_ResumeBgm(g_SndBgmId);
                }
                g_ScriptWorkRecord->flags_00 = 0;
                Game_ClearScriptActive();
                D_801448EB = 0;
                *state     = 0;
                D_801448ED = 0;
            }
            break;
    }
}
