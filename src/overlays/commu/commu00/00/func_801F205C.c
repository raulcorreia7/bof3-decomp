#include "commu00_00.h"

MATCH void func_801F205C(void) {
    u32 record_byte;
    u8  entry_index;
    u8  variant;
    u16 message_id;
    u8* src;
    u8* edp;
    s32 i;
    u8  index;

    record_byte = g_SaveData.fairy_jobs[g_SaveData.scene_event.selection].unk_03;
    entry_index = record_byte >> 4;
    variant     = entry_index;
    if (D_801F26CC[variant].count == 0) {
        message_id = D_801F26CC[variant].message_id;
        if (variant == 0) {
            FAIRY_EVENT_STEP = 2;
        } else {
            index                       = g_SaveData.scene_event.step;
            index                       = index + 1;
            MEM_PTR(u8, 0x801448ECu)[0] = index;
        }
    } else {
        /* FAKE: for-loop init + indexed copy, the shape the matched twin
         * Fairy_GrantGift in this unit uses: cc1 emits the `i = 0` before the
         * call-result copy (retail `move v1,zero` at 0xb0, `move a0,v0` at
         * 0xb4). */
        src = Item_GetRecord(record_byte & 0xF, g_SaveData.fairy_jobs[g_SaveData.scene_event.selection].record_state);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = src[i];
        }
        D_801490E4[0] = 0;
        edp           = &g_SaveData.scene_event.selection;
        if (Item_Add(g_SaveData.fairy_jobs[*edp].unk_03 & 0xF, g_SaveData.fairy_jobs[*edp].record_state,
                     /* The pending count's low byte: retail loads one byte. */
                     ((u8*)D_801F26CC)[entry_index * 6 + 4], 0) &
            0xFF) {
            g_SaveData.fairy_jobs[*edp].record_state = 0;
            g_SaveData.fairy_jobs[*edp].unk_03       = 0;
            message_id                               = D_801F26CC[entry_index].message_id;
        } else {
            message_id = D_801F26CC[entry_index].item_id;
        }
        FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
    }
    Message_StartAreaMessage((s16)message_id);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
}
