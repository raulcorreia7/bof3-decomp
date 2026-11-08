#include "sisyou_00.h"

/* Shared frontend phase byte. */

/* Active master id; the master bit buffers follow at +0x63B and +0x693. */

/* Per-master halfword table. */

/* Master-menu step counter. */

/* Party-slot record index (stride 0x140). */

/* Master-menu flags byte. */

/* Per-master skill-grant rows: level threshold and skill id. */

/* Queued-skill name copy buffer and its pending flag. */

#ifdef NON_MATCHING
NON_MATCHING void func_801D3A24(void) {
    s32 rec;
    u8  chr_master;
    u8  diff;
    u8  done;
    s32 i;
    u8  skill;
    s32 k;

    done = 0;
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    rec        = g_Game.members[g_MasterMenuCursor].character_index;
    chr_master = g_Characters[rec].master_id;
    if (chr_master == g_SceneEventSelection) {
        diff = g_Characters[rec].level - g_Characters[rec].master_level;
        switch (chr_master) {
            case MASTER_BAIS:
                if (diff >= 3 && !(g_MasterRewardFlags & (1 << CHAR_INDEX_TEEPO))) {
                    g_MasterRewardFlags |= 1 << CHAR_INDEX_TEEPO;
                    func_801D39CC(g_Game.members[g_MasterMenuCursor].character_index);
                    done = 1;
                }
                break;
            case MASTER_LANG:
                if (diff >= 3) {
                    if (SYS_TestFlag(&g_SceneEventSelection + 0x63B, 0x6C) == 0) {
                        if (Item_Add(ITEM_CAT_ACCESSORY, ACCESSORY_CUPIDS_LYRE, 1, 0) & BYTE_MASK) {
                            SYS_SetFlag(&g_SceneEventSelection + 0x63B, 0x6C);
                            func_801D39CC(g_Game.members[g_MasterMenuCursor].character_index);
                            done = 1;
                        }
                    }
                }
                break;
            case MASTER_LEE:
                if (diff >= 3 && !(g_MasterRewardFlags & (1 << CHAR_INDEX_REI))) {
                    g_MasterRewardFlags |= 1 << CHAR_INDEX_REI;
                    func_801D39CC(g_Game.members[g_MasterMenuCursor].character_index);
                    done = 1;
                }
                break;
            case MASTER_WYNN:
                if (diff >= 3 && !(g_MasterRewardFlags & (1 << CHAR_INDEX_MOMO))) {
                    g_MasterRewardFlags |= 1 << CHAR_INDEX_MOMO;
                    func_801D39CC(g_Game.members[g_MasterMenuCursor].character_index);
                    done = 1;
                }
                break;
            default:
                for (i = 0; i < 12; i += 2) {
                    if (diff < g_MasterSkills[g_SceneEventSelection][i / 2].level) {
                        continue;
                    }
                    skill = g_MasterSkills[g_SceneEventSelection][i / 2].ability;
                    if (BIT_ARRAY_TEST(g_LearnedAbilities, skill)) {
                        continue;
                    }
                    if (!(Char_AddAbility(skill, g_Game.members[g_MasterMenuCursor].character_index, 0, 0) & 0xFF)) {
                        continue;
                    }
                    func_801D39CC(g_Game.members[g_MasterMenuCursor].character_index);
                    for (k = 0; k < 12; k++) {
                        D_801490F8[k] =
                            ((const u8*)(g_Abilities))[g_MasterSkills[g_SceneEventSelection][i / 2].ability * 0x14 + k];
                    }
                    done       = 1;
                    D_80149104 = 0;
                    skill      = g_MasterSkills[g_SceneEventSelection][i / 2].ability;
                    BIT_ARRAY_SET(g_LearnedAbilities, skill);
                    break;
                }
                break;
        }
    }
    if (done) {
        Message_StartAreaMessage((s16)(g_MasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_SKILL_LEARNED));
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
    }
    g_MasterSubStep += 1;
}
#else
INCLUDE_ASM(func_801D3A24);
#endif
