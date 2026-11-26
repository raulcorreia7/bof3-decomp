#include "battle_03.h"

#define ENEMY_SCRIPT_PTR(i) (g_BattleCurrentEnemy->script + (i))

/* func_801E2314 */
MATCH void Battle_RequestEnemyScript(u32 script_index) {
    /* FAKE: volatile-drop cast steers switch codegen. */
    switch (SELF(PartyMember)->facing) {
        case 0: {
            s32 index = script_index & BYTE_MASK;
            Script_Request(ENEMY_SCRIPT_PTR(index)[0] & 0x7F);
            if (ENEMY_SCRIPT_PTR(index)[0] & 0x80u) {
                SELF(PartyMember)->unk_2A = 1u;
            } else {
                SELF(PartyMember)->unk_2A = 0u;
            }
            break;
        }
        case 1: {
            s32 index = script_index & BYTE_MASK;
            Script_Request(ENEMY_SCRIPT_PTR(index)[0] & 0x7F);
            if (ENEMY_SCRIPT_PTR(index)[0] & 0x80u) {
                SELF(PartyMember)->unk_2A = 0u;
            } else {
                SELF(PartyMember)->unk_2A = 1u;
            }
            break;
        }
        case 2: {
            s32 index = script_index & BYTE_MASK;
            Script_Request(ENEMY_SCRIPT_PTR(index)[1] & 0x7F);
            if (ENEMY_SCRIPT_PTR(index)[1] & 0x80u) {
                SELF(PartyMember)->unk_2A = 1u;
            } else {
                SELF(PartyMember)->unk_2A = 0u;
            }
            break;
        }
        case 3: {
            s32 index = script_index & BYTE_MASK;
            Script_Request(ENEMY_SCRIPT_PTR(index)[1] & 0x7F);
            if (ENEMY_SCRIPT_PTR(index)[1] & 0x80u) {
                /* FAKE: non-volatile store fills merged-tail delay slot. */
                SELF(PartyMember)->unk_2A = 0u;
            } else {
                SELF(PartyMember)->unk_2A = 1u;
            }
            break;
        }
    }
}
