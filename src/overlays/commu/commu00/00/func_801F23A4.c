#include "commu00_00.h"

/* Exe loader entry point (func_801636A0): resets the request block for `arg0`. */

/* FAKE: the original reads the variant byte through its address, kept in one register. */
MATCH void func_801F23A4(void) {
    s8* variant;

    variant = &g_SceneEventStep;
    switch (*variant) {
        case 0:
            D_801F2945 = g_SndBGMId;
            SND_StopSequence(((u8*)g_SelectionCues)[D_801F2945 * 4], D_80181EBB[D_801F2945 * 4]);
            SND_StartXAStream(D_801F2944 == 0 ? 8 : 10, 1);
            /* FAKE: the original spells this increment off the neighboring mode
             * byte, so the switch's cached g_SceneEventStep address is not reused; both
             * expressions resolve to 0x801448EC. */
            ((s8*)&g_SceneEventMode)[1] += 1;
            break;
        case 1:
            if ((SND_IsXAIdle() & BYTE_MASK) != 0) {
                Message_StartAreaMessage(0x2A1);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
                *variant += 1;
            }
            break;
        case 2:
            if (g_GameStateIndex != *variant) {
                SND_PlayBGM(D_801F2945, 100, 8);
                g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
                func_801F1684();
                func_801F1638();
            }
            break;
    }
}
