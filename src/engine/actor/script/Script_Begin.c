#include "engine/slus/slus.h"

/* Selects the stream entry for `selector`: a selector with bit 7 set picks the
 * entry from the current hint's mode row, otherwise it is kept as the entry
 * index; then points unk_50 at that entry's script unless bit 0 of unk_24
 * hands it to func_8014DC08. */
MATCH void Script_Begin(s32 script_index, s32 position) {
    u8(*modes)[3];
    u8* table;
    s32 entry;
    u8  flags;
    u8  selector;
    u16 code;
    u8  hint;

    selector = script_index;
    code     = position;
    if (script_index & 0x80) {
        if (!(SELF(Actor)->active_flags & 0x2)) {
            modes                = (u8(*)[3])D_80181B34;
            hint                 = g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK;
            SELF(Actor)->angle_x = modes[hint][SELF(Actor)->unk_2C];
            SELF(Actor)->angle_y = SELF(Actor)->sheet_row;
            SELF(Actor)->active_flags ^= 3;
        }
        entry = ((s32*)&D_80181C7C)[SELF(Actor)->angle_x];
        entry += (script_index & 0x7F) * 4;
        Area_SceneSelectRecord(*(u16*)entry);
        SELF(Actor)->script_record = *(u8*)(entry + 2);
        SELF(Actor)->mirror        = *(u8*)(entry + 3);
    } else {
        flags = SELF(Actor)->active_flags;
        if (flags & 0x2) {
            flags &= 0xFC;
            /* FAKE: the retail call passes script_index as a third argument the real prototype lacks. */
            ((void (*)(s32, s32, s32))Party_MemberLoadSprite)((u8)SELF(Actor)->angle_x, (SELF(Actor)->angle_y / 80) & BYTE_MASK, script_index);
            SELF(Actor)->active_flags = SELF(Actor)->active_flags | flags;
        }
        SELF(Actor)->script_record = selector;
    }
    if (SELF(Actor)->active_flags & 0x1) {
        Actor_SelectSprite(SELF(Actor)->script_record);
    } else {
        table = (u8*)g_Scripts;
        table += ((s32*)table)[SELF(Actor)->unk_2C];
        SELF(Actor)->script = table + ((u16*)table)[SELF(Actor)->script_record];
    }
    Script_Seek(code);
}
