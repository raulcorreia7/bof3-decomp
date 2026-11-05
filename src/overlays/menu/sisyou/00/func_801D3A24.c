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
    s32 idx;
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
    idx        = g_MasterMenuCursor * BATTLE_PARTY_STRIDE;
    rec        = D_80145FCC.bytes[idx];
    chr_master = g_Characters[rec].master_id;
    if (chr_master == D_801448ED) {
        diff = g_Characters[rec].level - g_Characters[rec].master_level;
        switch (chr_master) {
            case 0xB:
                if (diff >= 3 && !(D_80144F59 & 8)) {
                    D_80144F59 |= 8;
                    func_801D39CC(D_80145FCC.bytes[idx]);
                    done = 1;
                }
                break;
            case 0xC:
                if (diff >= 3) {
                    if (SYS_TestFlag(&D_801448ED + 0x63B, 0x6C) == 0) {
                        if (Item_Add(ITEM_CAT_ACCESSORY, ACCESSORY_CUPIDS_LYRE, 1, 0) & BYTE_MASK) {
                            SYS_SetFlag(&D_801448ED + 0x63B, 0x6C);
                            func_801D39CC(D_80145FCC.bytes[g_MasterMenuCursor * BATTLE_PARTY_STRIDE]);
                            done = 1;
                        }
                    }
                }
                break;
            case 0xD:
                if (diff >= 3 && !(D_80144F59 & 0x10)) {
                    D_80144F59 |= 0x10;
                    func_801D39CC(D_80145FCC.bytes[idx]);
                    done = 1;
                }
                break;
            case 0xE:
                if (diff >= 3 && !(D_80144F59 & 0x20)) {
                    D_80144F59 |= 0x20;
                    func_801D39CC(D_80145FCC.bytes[idx]);
                    done = 1;
                }
                break;
            default:
                for (i = 0; i < 12; i += 2) {
                    if (diff < g_MasterSkills[D_801448ED][i / 2].level) {
                        continue;
                    }
                    skill = g_MasterSkills[D_801448ED][i / 2].ability;
                    if (((u32*)(&D_801448ED + 0x693))[skill >> 5] & (1 << (skill& 0x1F))) {
                        continue;
                    }
                    if (!(Char_AddAbility(skill, D_80145FCC.bytes[g_MasterMenuCursor * BATTLE_PARTY_STRIDE], 0, 0) &
                          0xFF)) {
                        continue;
                    }
                    func_801D39CC(D_80145FCC.bytes[g_MasterMenuCursor * BATTLE_PARTY_STRIDE]);
                    for (k = 0; k < 12; k++) {
                        D_801490F8[k] =
                            ((const u8*)(g_Abilities))[g_MasterSkills[D_801448ED][i / 2].ability * 0x14 + k];
                    }
                    done       = 1;
                    D_80149104 = 0;
                    skill      = g_MasterSkills[D_801448ED][i / 2].ability;
                    ((u32*)(&D_801448ED + 0x693))[skill >> 5] |= 1 << (skill & 0x1F);
                    break;
                }
                break;
        }
    }
    if (done) {
        Message_StartAreaMessage((s16)(g_MasterMessageIds[D_801448ED] + 0xE));
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
    }
    g_MasterSubStep += 1;
}
#else
INCLUDE_ASM(func_801D3A24);
#endif
