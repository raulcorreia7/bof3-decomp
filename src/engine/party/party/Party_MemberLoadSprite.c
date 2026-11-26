#include "engine/game/00/game_00.h"

/* func_801C1254 */
/* Loads the party member's field sprite into the work record: the character sprites section, sprite page, sheet row,
 * CLUT selector (party_slot + 0x78), palette type and the slot's palette. */
MATCH void Party_MemberLoadSprite(s32 character_id, s32 party_slot) {
    Actor*    work;
    const u8* base;
    const u8* entry;
    s32       index;
    s32       key;
    s32       masked;
    u8        hint;
    s32       slot;
    /* FAKE: retail accumulates the record value in v0. */
    FAKE_REG(s32, value, "v0");
    Actor* first;
    u8*    next;
    Actor* next_5d;

    index = 0;
    key   = character_id & BYTE_MASK;
    hint  = g_EmiLoadedCharacterIndex;
    base  = D_80181B34[0];
    entry = base + (hint & 0x7F) * 3;
    do {
        if (entry[index & BYTE_MASK] == key) {
            /* The mode table hit leaves the loop with index at the match. */
            goto found;
        }
        index++;
    } while ((index & BYTE_MASK) < 3U);
found:
    GFX_PaletteFreeFadeTarget(SELF(void));

    first                         = SELF(Actor);
    masked                        = index & BYTE_MASK;
    first->unk_2C                 = masked;
    value                         = MEM(s32, 0x8003B800u + masked * 4);
    first->active_flags           = 1;
    next                          = SELF(u8) + 0x27u;
    first->unk_4C                 = value + (s32)MEM_PTR(s32, 0x8003B800u);
    next[0]                       = (party_slot + 0x78);
    slot                          = party_slot & BYTE_MASK;
    SELF(Actor)->palette_8bit     = PALETTE_TYPE_CELLS_2;
    SELF(Actor)->sheet_page       = 5;
    SELF(Actor)->sheet_row        = (slot * 0x50);
    SELF(Actor)->unk_2B           = D_80181B1C[key];
    work                          = SELF(Actor);
    work->draw_layer              = g_AreaDrawMode;
    value                         = FIELD(s32, work, 0x70u) & ~0xFF;
    FIELD(s32, work, 0x70u)       = value;
    next_5d                       = SELF(Actor);
    FIELD(s32, work, 0x70u)       = value | (work->unk_2B != 0);
    next_5d->tint.bytes.rgb.r     = 0;
    SELF(Actor)->tint.bytes.rgb.g = 0;
    SELF(Actor)->tint.bytes.rgb.b = 0;
    SELF(Actor)->tint.bytes.flags = 0;
    GFX_PaletteLoad((slot * 0x40) + GAME_PALETTE_STAGE, 0);
}
