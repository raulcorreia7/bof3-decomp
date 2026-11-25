#include "game_00.h"

/* Reports whether the character may use the ability in this context: 0 is locked. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801AF5B0(s32 item_category, s32 character_index, s32 ability_type) {
    Ability* ability;
    u8       character;

    if ((u8)ability_type != 0) {
        ability = &g_Abilities[(u8)ability_type];
        switch ((u8)item_category) {
            case 0:
                return 1;

            case 1:
                character = g_CharSlot[g_PartyFieldOrder[(u8)character_index]];
                if (g_Characters[character].ap < (u8)Char_AbilityGetCost(character, (u8)ability_type, 0)) {
                    return 0;
                }
                if ((ability->targeting_flags & ABILITY_USABLE_IN_FIELD) != 0) {
                    break;
                }
                return 0;

            case 2:
                if (g_Game.members[(u8)character_index].chr.ap < (u8)Char_AbilityGetCost((u8)character_index, (u8)ability_type, 1)) {
                    return 0;
                }
                if ((ability->targeting_flags & ABILITY_USABLE_IN_BATTLE) == 0) {
                    return 0;
                }
                if ((g_Game.members[(u8)character_index].chr.status & STATUS_SILENCED) != 0 && (LOH(ability->element) & (ABILITY_SILENCEABLE << 8)) != 0) {
                    return 0;
                }
                if ((u8)ability_type == ABILITY_DISEMBOWEL && g_Game.members[(u8)character_index].chr.fatigue >= 5) {
                    return 0;
                }
                if ((u8)ability_type == ABILITY_BONEBREAK && *(u32*)&g_GameBonebreakTimer != 0) {
                    return 0;
                }
                if ((u8)ability_type == ABILITY_CELERITY && *(u32*)&g_GameCelerityTimer != 0) {
                    return 0;
                }
                if ((u8)ability_type == ABILITY_TRUMP && g_Game.members[(u8)character_index].chr.ap != 0) {
                    return 0;
                }
                if ((u8)ability_type != ABILITY_ACCESSION || g_Battle.encounter != 37) {
                    return 1;
                }
                return 0;
        }
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801AF5B0);
#endif
