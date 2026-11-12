#include "start_08.h"
#include "area/map.h"

MATCH void func_801D1B60(void) {
    u8*  saved_work;
    u8*  step;
    u16* counter;
    s8*  selection;
    s32  input;
    u16  i;
    u8   kind;
    u16  total;
    u8   value;

    Menu_DrawClutStrip(D_80144953);
    saved_work                 = TASK_BYTES;
    g_MenuPanelTasks[9].unk_0A = (s8)D_80148655;
    kind                       = D_801EC38C[(s8)D_80148655];
    TASK_SET(g_Game.members);
    g_MenuPanelTasks[10].u.addr.unk_10 = (s16)kind;
    if ((D_8014504A == 0 && ((g_GameRequestFlags & 0x1) || g_GameAreaId == AREA_ID_DESERT_OF_DEATH_MAP) && (func_801B6470(kind) & BYTE_MASK)) || (D_8014504A != 0 && (func_801D2190() & BYTE_MASK))) {
        g_MenuPanelTasks[9].unk_0C = 0;
    } else {
        g_MenuPanelTasks[9].unk_0C = 1;
    }
    TASK_SET(saved_work);
    input = PAD_GetRepeatedButtons(g_InputPressed & (PADLright | PADLleft));
    if (input & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_80148654 = 0;
        D_80148655 = D_80148655 - 1;
        if ((s8)D_80148655 < 0) {
            D_80148655 = 6;
        }
    }
    if (input & PADLright) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_80148654 = 0;
        D_80148655 = D_80148655 + 1;
        if ((s8)D_80148655 >= 7) {
            D_80148655 = 0;
        }
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        func_801D21F4();
        step     = &D_80148651;
        counter  = &g_GameEntrySubstate;
        total    = *counter + 1;
        value    = *step + 2;
        *step    = value;
        *counter = total;
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        selection = (s8*)&D_80148655;
        if (*selection == 6) {
            if (g_MenuPanelTasks[9].unk_0C == 0) {
                func_801D21F4();
                D_8014869C = 1;
                /* FAKE: retail takes the step counter's address before the increment. */
                (*(CampMenuStepCounter*)&g_GameEntrySubstate).value++;
                D_80148651++;
                return;
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        D_80148654                 = 5;
        g_MenuPanelTasks[7].state  = 1;
        g_MenuPanelTasks[8].state  = 1;
        g_MenuPanelTasks[9].state  = 1;
        g_MenuPanelTasks[10].state = 1;
        if (*selection == 0) {
            for (i = 0; i < (Party_CountOrder(PARTY_ORDER_FIELD) & BYTE_MASK); i++) {
                g_MenuPanelTasks[i + 4].state = 1;
            }
        } else if ((s8)D_80148655 == 5) {
            for (i = 0; i < (Party_CountOrder(PARTY_ORDER_FIELD) & BYTE_MASK); i++) {
                g_MenuPanelTasks[i + 4].state = 7;
            }
        } else {
            for (i = 0; i < (Party_CountOrder(PARTY_ORDER_FIELD) & BYTE_MASK); i++) {
                g_MenuPanelTasks[i + 4].state = 2;
            }
        }
        {
            u8* last = &D_80148651;
            *last    = *last + 1;
        }
    }
}
