#include "shop_00.h"

/* nonmatching unmeasured: tried branch at +0x001c; resource-selection if/else call layout; candidate 49.56%. resume:
 * retail if/else call layout for resource selection rebuilt from asm. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DE4C8(void) {
    u8* resource;
    u8  prev_index;
    u8  prev_side;
    u8  buttons;
    u8  count;
    u8  result;

    func_801DF6A8();
    if (D_801E6254 == GAME_NONE) {
        resource = Resource_GetText(0x60);
    } else {
        TEXT_SetVariable(0, 5, g_Characters[MEM_PTR(u8, g_CharSlot)[D_801E6254]].name);
        resource = Resource_GetText(0x61);
    }
    UI_DrawText(26, 20, 0, TEXT_LENGTH_MAX, resource);
    buttons    = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    count      = Party_CountOrder(PARTY_ORDER_FIELD);
    prev_side  = D_80148658;
    prev_index = D_80148659;
    if ((buttons & (PADLright | PADLleft)) && D_801E6250 != 0) {
        D_80148658 ^= 1;
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
        D_80148659 -= 1;
        if ((s8)D_80148659 < 0) {
            D_80148659 = D_80148658 != 0 ? D_801E6250 - 1 : count - 1;
        }
    } else if (buttons & PADLdown) {
        D_80148659 += 1;
        if (D_80148658 == 0) {
            if (count - 1 < (s8)D_80148659) {
                D_80148659 = 0;
            }
        } else if (D_801E6250 - 1 < (s8)D_80148659) {
            D_80148659 = 0;
        }
    }
    if (prev_side != D_80148658 || prev_index != D_80148659) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if (g_InputMasks[MENU_INPUT_CONFIRM] & g_InputPressed) {
        if (D_8014865A == 0x7F) {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            D_8014865A = D_80148658;
            D_8014865D = D_80148659;
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
        SND_PlayCue(EMI_CUE_ID(1, 6));
        if (D_8014865A != 0x7F) {
            D_8014865A = 0x7F;
            D_8014865D = 0x7F;
            return;
        }
        D_80148652 = 0;
        D_80148651 += 1;
        UI_SetMode(UI_MODE_FAST_FADE_OUT);
    }
}
#else
INCLUDE_ASM(func_801DE4C8);
#endif
