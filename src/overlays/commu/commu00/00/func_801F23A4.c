#include "commu00_00.h"

/* Exe loader entry point (func_801636A0): resets the request block for `arg0`. */

/* FAKE: the original reads the variant byte through its address, kept in one register. */
MATCH void func_801F23A4(void) {
    s8* variant;

    variant = &g_SceneEventState.step;
    switch (*variant) {
        case 0:
            D_801F2945 = g_SndBGMId;
            SND_SeqStop(((u8*)g_SelectionSepSlots)[D_801F2945 * 4], g_SelectionSequences[D_801F2945 * 4]);
            SND_XAStartStream(D_801F2944 == 0 ? 8 : 10, 1);
            /* FAKE: the original spells this increment off the neighboring mode
             * byte, so the switch's cached g_SceneEventState.step address is not reused; both
             * expressions resolve to 0x801448EC. */
            ((s8*)&g_SceneEventMode)[1] += 1;
            break;
        case 1:
            if ((SND_XAIsIdle() & BYTE_MASK) != 0) {
                MESSAGE_START_WAIT(MSG_AREA175_SEE_YOU_LATER_END);
                *variant += 1;
            }
            break;
        case 2:
            if (g_GameStateIndex != *variant) {
                SND_BGMPlay(D_801F2945, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
                g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
                func_801F1684();
                func_801F1638();
            }
            break;
    }
}
