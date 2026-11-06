#include "start_08.h"

MATCH void func_801D3884(void) {
    s32 trigger;
    s8  step_down;
    u8  step_up;
    u8* state;
    u8* counter;

    Menu_DrawClutStrip(D_80144953);
    D_801484CC = 0x17;
    D_80148624 = 1;
    D_80148628 = D_80148508 + 0x2A;
    D_8014862A = D_8014850A + 7;
    trigger    = INPUT_REPEATED(g_InputPressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    D_80148510 = 0xFF;
    if (trigger & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        D_80148514 = 0x32;
        step_down  = D_8014850E - 1;
        D_8014850E = step_down;
        if (step_down < 0) {
            D_8014850E = 3;
        }
        /* Both directions store the stepped entry. */
        goto store_selection;
    }
    if (trigger & PADLright) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        D_80148514 = 0x31;
        step_up    = D_8014850E + 1;
        D_8014850E = step_up;
        if ((step_up & BYTE_MASK) >= 4U) {
            D_8014850E = 0;
        }
    store_selection:
        /* Shared tail of both step directions. */
        D_8014850F = s_ChoiceMenuValues[D_8014850E];
    }
    if (g_InputPressed & D_80145AC2) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        D_80148529 = 6;
        D_8014852A = 0xF;
        D_80148528 = 1;
        D_8014852C = 0xB4;
        D_8014852E = 0x3C;
        D_80148533 = 0;
        D_80148534 = 0xFF;
        state      = &D_80148652;
        /* FAKE: scheduler hoists the state load past the stores. */
        MATCH_BARRIER();
        D_80148532 = D_8014850E;
        *state += 1;
        return;
    }
    if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        counter = &D_80148651;
        *counter -= 3;
    }
}
