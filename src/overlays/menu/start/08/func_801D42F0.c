#include "start_08.h"

extern s8 D_80148656;

MATCH void func_801D42F0(void) {
    u8* items;
    u8* counts;
    s8* sel;
    s8* current;
    s32 input;
    u8  count;
    u8  old;
    u8  result;

    Menu_DrawClutStrip(D_80144953);
    items  = &D_801C893C[D_8014850E][D_80148510];
    counts = &D_801C8950[D_8014850E][D_80148510];
    Message_SetVariable(0, 0xC, (const u8*)&g_Items[*items]);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x19;
    D_801485DC                                                  = 1;
    D_801485E0                                                  = 0xB6;
    sel                                                         = &D_80148656;
    D_801485E2                                                  = *sel * 0x36 + 0x3E;
    count                                                       = Party_CountOrder(PARTY_ORDER_FIELD);
    input                                                       = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    old                                                         = *sel;
    if (input & PADLup) {
        *sel = old - 1;
        if (*sel < 0) {
            *sel = count - 1;
        }
    } else if (input & PADLdown) {
        *sel = old + 1;
        if ((s8)(old + 1) > ((count & BYTE_MASK) - 1)) {
            *sel = 0;
        }
    }
    current = &D_80148656;
    if ((s8)old != *current) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }

    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        result = func_801E8C9C(g_CharSlot[g_PartyFieldOrder[*current]], *items, 0) & BYTE_MASK;
        if ((result == 0) || (result == 4)) {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            *counts -= 1;
            if (*counts != 0) {
                return;
            }
            *items = 0;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 7));
            return;
        }
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
    } else {
        return;
    }
    D_801485DC        = 0;
    *(u8*)&D_80148511 = 0xFF;
    D_80148651 -= 4;
}
