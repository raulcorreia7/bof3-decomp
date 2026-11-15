#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DE4C8(void) {
    u8  prev_index;
    u8  prev_side;
    u8* side;
    u8* index;
    s8* cursor;
    s32 buttons;
    u8  count;
    u8  result;

    func_801DF6A8();
    if (D_801E6254 == GAME_NONE) {
        UI_DrawText(26, 20, 0, TEXT_LENGTH_MAX, Message_GetText(0x60));
    } else {
        Message_SetVariable(0, 5, g_Characters[MEM_PTR(u8, g_CharSlot)[D_801E6254]].name);
        UI_DrawText(26, 20, 0, TEXT_LENGTH_MAX, Message_GetText(0x61));
    }
    buttons    = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    count      = Party_CountOrder(PARTY_ORDER_FIELD);
    side       = (u8*)&D_80148658;
    prev_side  = *side;
    prev_index = D_80148659;
    if ((buttons & (PADLright | PADLleft)) && D_801E6250 != 0) {
        *side ^= 1;
    }
    if (D_80148658 == 0) {
        if (count - 1 < D_80148659) {
            D_80148659 = count - 1;
        }
    } else {
        if (D_801E6250 - 1 < D_80148659) {
            D_80148659 = D_801E6250 - 1;
        }
    }
    if (buttons & PADLup) {
        index = (u8*)&D_80148659;
        if ((s8)(*index -= 1) < 0) {
            *index = (D_80148658 == 0) ? count - 1 : D_801E6250 - 1;
        }
    } else if (buttons & PADLdown) {
        s32 value;

        index = (u8*)&D_80148659;
        value = (s8)(*index += 1);
        if (D_80148658 == 0) {
            if (count - 1 < value) {
                D_80148659 = 0;
            }
        } else if (D_801E6250 - 1 < value) {
            D_80148659 = 0;
        }
    }
    if (prev_side != D_80148658 || prev_index != D_80148659) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (g_InputMasks[MENU_INPUT_CONFIRM] & g_InputPressed) {
        cursor = &D_8014865A;
        if (*cursor == 0x7F) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            *cursor    = (u8)D_80148658;
            D_8014865D = (u8)D_80148659;
            return;
        }
        result     = func_801DF478();
        D_801E6254 = result;
        SND_PlayCue(result == GAME_NONE ? 0x103 : 0x107);
        D_8014865A = 0x7F;
        D_8014865D = 0x7F;
        return;
    }
    if (g_InputMasks[MENU_INPUT_CANCEL] & g_InputPressed) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        cursor = &D_8014865A;
        if (*cursor != 0x7F) {
            *cursor    = 0x7F;
            D_8014865D = 0x7F;
            return;
        }
        g_MenuStep.state = 0;
        g_MenuStep.sub_step += 1;
        UI_SetMode(UI_MODE_FAST_FADE_OUT);
    }
}
#else
INCLUDE_ASM(func_801DE4C8);
#endif
