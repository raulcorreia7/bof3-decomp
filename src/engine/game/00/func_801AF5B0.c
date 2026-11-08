#include "game_00.h"

/* nonmatching unmeasured: tried regalloc: first-compare tail layout; andi placement vs retail. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801AF5B0(s32 item_category, s32 character_index, s32 ability_kind) {
    MATCH_REG(s32, ch, "s1");
    /* FAKE: pin the argument roles to retail s1, s2 and s3. */
    MATCH_REG(s32, kind, "s2");
    MATCH_REG(const u8*, ability, "s3");
    s32 category;
    s32 mapped_character;
    /* FAKE: the character offset stays in retail s0. */
    MATCH_REG(u32, character_offset, "s0");
    u32 required_level;
    u32 learned_level;

    ch   = character_index;
    kind = ability_kind;
    if ((u8)kind == 0u) {
        return 0;
    }
    ability  = (const u8*)&g_Abilities[(u8)kind];
    category = item_category & BYTE_MASK;
    if (category == 1) {
        goto case_1;
    }
    if (category < 2) {
        return 1;
    }
    if (category == 2) {
        goto case_2;
    }
    return 1;
case_1:
    mapped_character = g_CharSlot[g_PartyFieldOrder[(u8)ch]];
    character_offset = (u32)mapped_character * PARTY_RECORD_STRIDE;
    required_level   = Char_GetAbilityCost((u8)mapped_character, (u8)kind, 0u) & BYTE_MASK;
    learned_level    = g_Characters[mapped_character].ap;
    if (learned_level < required_level)
        return 0;
    if (ability[0xC] & 1u)
        return 1;
    return 0;
case_2:
    character_offset = (u32)(u8)ch * BATTLE_PARTY_STRIDE;
    required_level   = Char_GetAbilityCost((u8)ch, (u8)kind, 1u) & BYTE_MASK;
    learned_level    = *(const u16*)(D_80145F1A + character_offset);
    if (learned_level < required_level)
        return 0;
    if ((ability[0xC] & 2u) == 0u)
        return 0;
    if ((*(const u16*)(D_80145F10 + character_offset) & 0x10u) != 0u && (*(const u16*)(ability + 0x10) & 0x400u) != 0u)
        return 0;
    if ((u8)kind == ABILITY_DISEMBOWEL && g_Game.members[(u8)ch].chr.fatigue >= 5u)
        return 0;
    if ((u8)kind == ABILITY_BONEBREAK && *(u32*)&g_GameBonebreakTimer != 0u)
        return 0;
    if ((u8)kind == ABILITY_CELERITY && *(u32*)&g_GameCelerityTimer != 0u)
        return 0;
    if ((u8)kind == ABILITY_TRUMP && g_Game.members[(u8)ch].chr.ap != 0u)
        return 0;
    if ((u8)kind == ABILITY_ACCESSION && g_Battle.encounter == 37u)
        return 0;
    return 1;
}
#else
INCLUDE_ASM(func_801AF5B0);
#endif
