#include "game_00.h"

/* Reports whether the character may use the ability in this context: 0 is locked. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801AF5B0(s32 item_category, s32 character_index, s32 ability_type) {
    volatile Ability* ability;
    u8                type;
    u8                character;
    u32               required_level;
    u32               learned_level;

    type = ability_type & BYTE_MASK;
    if (type == 0) {
        return 0;
    }
    ability = &g_Abilities[type];
    switch (item_category & BYTE_MASK) {
        case 1:
            character      = g_CharSlot[g_PartyFieldOrder[character_index & BYTE_MASK]];
            required_level = Char_AbilityGetCost(character, type, 0) & BYTE_MASK;
            learned_level  = g_Characters[character].ap;
            if (learned_level < required_level) {
                return 0;
            }
            if ((ability->targeting_flags & ABILITY_USABLE_IN_FIELD) != 0) {
                return 1;
            }
            return 0;

        case 2:
            character      = character_index & BYTE_MASK;
            required_level = Char_AbilityGetCost(character, type, 1) & BYTE_MASK;
            learned_level  = g_Game.members[character].chr.ap;
            if (learned_level < required_level) {
                return 0;
            }
            if ((ability->targeting_flags & ABILITY_USABLE_IN_BATTLE) == 0) {
                return 0;
            }
            if ((g_Game.members[character].chr.status & STATUS_SILENCED) != 0 && (ability->ability_flags & ABILITY_SILENCEABLE) != 0) {
                return 0;
            }
            if (type == ABILITY_DISEMBOWEL && g_Game.members[character].chr.fatigue >= 5) {
                return 0;
            }
            if (type == ABILITY_BONEBREAK && *(u32*)&g_GameBonebreakTimer != 0) {
                return 0;
            }
            if (type == ABILITY_CELERITY && *(u32*)&g_GameCelerityTimer != 0) {
                return 0;
            }
            if (type == ABILITY_TRUMP && g_Game.members[character].chr.ap != 0) {
                return 0;
            }
            if (type == ABILITY_ACCESSION && g_Battle.encounter == 37) {
                return 0;
            }
            return 1;

        default:
            return 1;
    }
}
#else
INCLUDE_ASM(func_801AF5B0);
#endif
