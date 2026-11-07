#include "area030_04.h"

/* Reacts to the pad repeat decode: closes or reopens the panel,
 * advances the panel cursor through the scratchpad work record, and redraws the
 * two panel lines with the selected record word and fishing-rod/lure id. */
MATCH void func_801DCDB8(void) {
    u16* pad_state;
    u16  pad;
    s32  input;
    u16  value;

    pad_state = &g_InputPressed;
    input     = INPUT_REPEATED(*pad_state, (PADLup | PADLdown));
    pad       = *pad_state;

    if (pad & g_InputMasks[FISHING_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_801442AC = 0xFFFF;
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *MATCH_VOLATILE_PTR(u8, &D_80144287) |= 0x80;
        FISHING_STATE->sub_index_03 -= 1;
        FISHING_STATE->flag_04 = 0;
        return;
    }
    if (pad & g_InputMasks[FISHING_INPUT_CAST]) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *MATCH_VOLATILE_PTR(u8, &D_80144287) |= 2;
        FISHING_STATE->flag_04 += 1;
    } else if (input & (PADLup | PADLdown)) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *MATCH_VOLATILE_PTR(u8, &D_80144287) ^= 1;
        D_80144281 ^= 7;
        FISHING_STATE->flag_04 -= 1;
    }

    if (!(D_80144287 & 1)) {
        UI_DrawText(0x1D, 0x14, 0, 0xFF, (u8*)(FISHING_TEXT_BANK + D_800100A2));
    } else {
        UI_DrawText(0x1D, 0x14, 0, 0xFF, (u8*)(FISHING_TEXT_BANK + D_800100A4));
    }

    if (!(D_80144287 & 0x80)) {
        if (!(D_80144287 & 1)) {
            value = g_FishingRod; /* FISHING_ROD */
            value = (value != 0) ? value + 4 : 0xFFFF;
        } else {
            value = g_FishingLure; /* FISHING_LURE */
            value = (value != 0) ? value + 4 : 0xFFFF;
        }
        D_801442AC = value;
    }
    Menu_DrawCursorSprite(0x1C, (D_80144287 & 1) * 0x10 + 0x58, 0);
}
