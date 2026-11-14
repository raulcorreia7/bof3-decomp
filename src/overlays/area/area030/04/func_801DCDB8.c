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
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_801442AC = 0xFFFF;
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *FAKE_VOLATILE_PTR(u8, &D_80144287) |= 0x80;
        FISHING_STATE->sub_index_03 -= 1;
        FISHING_STATE->flag_04 = 0;
        return;
    }
    if (pad & g_InputMasks[FISHING_INPUT_CAST]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *FAKE_VOLATILE_PTR(u8, &D_80144287) |= 2;
        FISHING_STATE->flag_04 += 1;
    } else if (input & (PADLup | PADLdown)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *FAKE_VOLATILE_PTR(u8, &D_80144287) ^= 1;
        D_80144281 ^= 7;
        FISHING_STATE->flag_04 -= 1;
    }

    if (!(D_80144287 & 0x1)) {
        UI_DrawText(29, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_EQUIP_ROD));
    } else {
        UI_DrawText(29, 20, 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_EQUIP_LURE));
    }

    if (!(D_80144287 & 0x80)) {
        if (!(D_80144287 & 0x1)) {
            value = g_FishingRod;
            value = (value != 0) ? value + 4 : 0xFFFF;
        } else {
            value = g_FishingLure;
            value = (value != 0) ? value + 4 : 0xFFFF;
        }
        D_801442AC = value;
    }
    Menu_DrawCursorSprite(28, (D_80144287 & 0x1) * 16 + 88, 0);
}
