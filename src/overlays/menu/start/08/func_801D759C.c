#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D759C(void) {
    u8* panel;
    u8* panel_state;
    u8* battle_message;
    s32 count;
    s32 input;
    s32 previous;

    panel       = g_BattleChoicePanel;
    panel_state = &D_80148578;
    Menu_DrawClutStrip(*((u8*)&g_WindowStyle + 1));
    D_80148578 = (D_801ED648 != 0) ? 3 : 1;
    D_80148624 = 0;
    if (g_BattleMessageState == 0) {
        panel_state[0x64] = 1;
        D_801485E7        = 1;
        battle_message    = (u8*)&g_BattleMessageState;
        D_801485E0        = *(u16*)(battle_message + 1);
        D_801485E2        = *(u16*)(battle_message + 3) + (D_8014857A * 0x36);
    } else {
        panel_state[0x64] = 0;
    }

    Message_SetVariable(0, 5, (const u8*)&g_Characters[g_CharSlot[g_PartyFieldOrder[D_8014857A]]]);
    D_801484CC = 0x2F;
    input      = INPUT_GetRepeatedButtons(g_InputPressed & 0xF000);
    D_8014857C = 0xFF;
    D_8014857D = 0xFF;
    count      = Party_CountOrder(PARTY_ORDER_FIELD);
    previous   = D_8014857A;

    if (input & 0x1000) {
        SND_PlayCue(0x100);
        D_8014857A--;
        if ((s8)D_8014857A < 0) {
            D_8014857A = count - 1;
        }
    } else if (input & 0x4000) {
        SND_PlayCue(0x100);
        D_8014857A++;
        if (count - 1 < D_8014857A) {
            D_8014857A = 0;
        }
    }
    if (D_801ED648 == 2) {
        panel[0x10] = 1;
    } else {
        panel[0x10] = 0;
        if (input & 0x8000) {
            SND_PlayCue(0x101);
            panel[9] = 0x32;
            panel[0x0B]--;
            if ((s8)panel[0x0B] < 0) {
                panel[0x0B] = 3;
            }
        } else if (input & 0x2000) {
            SND_PlayCue(0x101);
            panel[9] = 0x31;
            panel[0x0B]++;
            if (panel[0x0B] >= 4) {
                panel[0x0B] = 0;
            }
        }
    }
    if (D_8014857A != previous) {
        SND_PlayCue(0x101);
    }

    D_80148656 = D_8014857A;
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(0x104);
        D_8014857C = s_SkillOrderCursors[(s8)D_80148656][D_8014857B];
        D_80148651++;
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(0x106);
        D_801485DC = 0;
        D_80148651--;
    }
}
#else
INCLUDE_ASM(func_801D759C);
#endif
