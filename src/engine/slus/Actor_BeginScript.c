#include "engine/slus/slus.h"

/* Selects the stream entry for `selector`: a selector with bit 7 set picks the
 * entry from the current hint's mode row, otherwise it is kept as the entry
 * index; then points unk_50 at that entry's script unless bit 0 of unk_24
 * hands it to func_8014DC08. */
MATCH void Actor_BeginScript(s32 raw_selector, s32 raw_code) {
    u8(*modes)[3];
    u8* table;
    s32 entry;
    u8  flags;
    u8  selector;
    u16 code;
    u8  hint;

    selector = raw_selector;
    code     = raw_code;
    if (raw_selector & 0x80) {
        if (!(g_Task->active_flags & 0x2)) {
            modes          = (u8(*)[3])D_80181B34;
            hint           = g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK;
            g_Task->unk_64 = modes[hint][g_Task->unk_2C];
            g_Task->unk_68 = g_Task->unk_26;
            g_Task->active_flags ^= 3;
        }
        entry = ((s32*)&D_80181C7C)[g_Task->unk_64];
        entry += (raw_selector & 0x7F) * 4;
        Area_FindSceneRecord(*(u16*)entry);
        g_Task->unk_4B = *(u8*)(entry + 2);
        g_Task->unk_2A = *(u8*)(entry + 3);
    } else {
        flags = g_Task->active_flags;
        if (flags & 0x2) {
            flags &= 0xFC;
            Party_LoadMemberSprite((u8)g_Task->unk_64, (g_Task->unk_68 / 80) & BYTE_MASK, raw_selector);
            g_Task->active_flags = g_Task->active_flags | flags;
        }
        g_Task->unk_4B = selector;
    }
    if (g_Task->active_flags & 0x1) {
        Actor_SelectSprite(g_Task->unk_4B);
    } else {
        table = (u8*)g_ScriptTable;
        table += ((s32*)table)[g_Task->unk_2C];
        g_Task->script = table + ((u16*)table)[g_Task->unk_4B];
    }
    Actor_SeekScript(code);
}
