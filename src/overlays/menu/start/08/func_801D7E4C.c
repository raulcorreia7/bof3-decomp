#include "start_08.h"

extern u8 D_80148658;

MATCH void func_801D7E4C(void) {
    s32 buttons;
    u8  count;
    u8  old;
    u8  i;
    u8  state;
    u8* latch;
    u16 x;
    u16 y;
    u8* cursor;
    s8* sel;
    s8  result;

    u8* flag;
    Menu_DrawClutStrip(D_80144953);
    state = D_80148507;
    flag  = &D_80148624;
    latch = flag - 0x48;
    *flag = 0;
    if (state == 0) {
        x          = D_80148508;
        y          = (s8)D_80148658 * 0x36;
        *latch     = 1;
        D_801485E7 = 1;
        D_801485E0 = x;
        D_801485E2 = D_8014850A + y;
    } else {
        *latch = 0;
    }
    buttons = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    count   = Party_CountOrder(0);
    cursor  = &D_80148658;
    old     = *cursor;
    if (buttons & PADLup) {
        *cursor -= 1;
        if ((s8)*cursor < 0) {
            *cursor = count - 1;
        }
    } else if (buttons & PADLdown) {
        *cursor += 1;
        if ((s8)*cursor > count - 1) {
            *cursor = 0;
        }
    }
    sel = (s8*)&D_80148658;
    if ((s8)old != *sel) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    TEXT_SetVariable(0, 0xC, (const u8*)&g_Abilities[Party_GetAbilities(D_8014857A, D_8014857B, 0)[D_8014857C]]);
    D_801484CC = 0x30;
    if (g_InputPressed & D_80145AC2) {
        result     = func_801E7D20(g_CharSlot[D_80144F5A[D_8014857A]], g_CharSlot[D_80144F5A[*sel]],
                                   Party_GetAbilities(D_8014857A, D_8014857B, 0)[D_8014857C], 0);
        D_801ED654 = result;
        if (result == 1 || result == 5) {
            SND_PlayCue(EMI_CUE_ID(1, 9));
            return;
        }
        SND_PlayCue(EMI_CUE_ID(1, 7));
        return;
    }
    if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        SND_PlayCue(EMI_CUE_ID(1, 2));
        D_801485DC = 0;
        for (i = 0; i < Party_CountOrder(0); i++) {
            D_80148333[((i + 0xD) * 9) << 2] = 9;
            D_80148333[((i + 4) * 9) << 2]   = 8;
        }
        g_BattleChoicePhase = 3;
        D_8014857D          = 0xFF;
        latch               = &D_80148651;
        (*latch)--;
    }
}
