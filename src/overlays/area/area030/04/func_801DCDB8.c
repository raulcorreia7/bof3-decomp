#include "area030_04.h"

/* Reacts to the pad repeat decode: closes or reopens the panel,
 * advances the panel cursor through the scratchpad work record, and redraws the
 * two panel lines with the selected record word and fishing-rod/lure id. */
MATCH void func_801DCDB8(void) {
    u16* pad_state;
    u16  pad;
    s32  input;
    u16  value;

    pad_state = &g_PadStates[0].pressed;
    input     = INPUT_REPEATED(*pad_state, (PADLup | PADLdown));
    pad       = *pad_state;

    if (pad & g_InputMasks[FISHING_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_801442AC = 0xFFFF;
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *FAKE_VOLATILE_PTR(u8, &D_80144287) |= 0x80;
        SELF(FishingState)->sub_index -= 1;
        SELF(FishingState)->flag_04 = 0;
        return;
    }
    if (pad & g_InputMasks[FISHING_INPUT_CAST]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *FAKE_VOLATILE_PTR(u8, &D_80144287) |= 2;
        SELF(FishingState)->flag_04 += 1;
    } else if (input & (PADLup | PADLdown)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        /* FAKE: volatile access gives retail's register-address RMW; plain u8 pointer stayed at 76.5%. */
        *FAKE_VOLATILE_PTR(u8, &D_80144287) ^= 1;
        D_80144281 ^= 7;
        SELF(FishingState)->flag_04 -= 1;
    }

    if (!(D_80144287 & 0x1)) {
        UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_EQUIP_ROD));
    } else {
        UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_EQUIP_LURE));
    }

    if (!(D_80144287 & 0x80)) {
        if (!(D_80144287 & 0x1)) {
            value = g_FishingEquipment.rod_id;
            value = (value != 0) ? value + 4 : 0xFFFF;
        } else {
            value = g_FishingEquipment.lure_id;
            value = (value != 0) ? value + 4 : 0xFFFF;
        }
        D_801442AC = value;
    }
    UI_CursorDraw(28, (D_80144287 & 0x1) * 16 + 88, 0);
}
