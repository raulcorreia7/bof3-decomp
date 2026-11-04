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
        if (!(g_SpadWork->flags_24 & 2)) {
            modes              = (u8(*)[3])D_80181B34;
            hint               = g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK;
            g_SpadWork->unk_64 = modes[hint][g_SpadWork->unk_2C];
            g_SpadWork->unk_68 = g_SpadWork->unk_26;
            g_SpadWork->flags_24 ^= 3;
        }
        entry = ((s32*)&D_80181C7C)[g_SpadWork->unk_64];
        entry += (raw_selector & 0x7F) * 4;
        Area_FindSceneRecord(*(u16*)entry);
        g_SpadWork->unk_4B = *(u8*)(entry + 2);
        g_SpadWork->unk_2A = *(u8*)(entry + 3);
    } else {
        flags = g_SpadWork->flags_24;
        if (flags & 2) {
            flags &= 0xFC;
            func_801C1254((u8)g_SpadWork->unk_64, (g_SpadWork->unk_68 / 80) & BYTE_MASK, raw_selector);
            g_SpadWork->flags_24 = g_SpadWork->flags_24 | flags;
        }
        g_SpadWork->unk_4B = selector;
    }
    if (g_SpadWork->flags_24 & 1) {
        Actor_SelectScriptBank(g_SpadWork->unk_4B);
    } else {
        table = (u8*)g_ScriptBank;
        table += ((s32*)table)[g_SpadWork->unk_2C];
        g_SpadWork->source_50 = table + ((u16*)table)[g_SpadWork->unk_4B];
    }
    Actor_SeekScript(code);
}
