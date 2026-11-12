#include "area108_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4414(void) {
    PartyMember* member;
    u8           facing;
    u8           i;
    u8           index;
    u32          mask;

    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (g_Game.members[0].chr.character_id != CHAR_ID_GARR) {
        return;
    }
    facing = g_Game.members[0].facing & 7;
    for (index = 0; index < 5; index++) {
        if (facing == D_801F636C[index * 3 + 2] && D_80147B26[0] == D_801F636C[index * 3] && D_80147B26[2] == D_801F636C[index * 3 + 1]) {
            break;
        }
    }
    switch (index) {
        case 0:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                member = &g_Game.members[i];
                if (member->pos.x.part.integer >= 0x28 && (u32)(member->pos.y.part.integer - 0x53) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask & BYTE_MASK);
            if (SYS_TestFlag(g_SceneEventFlags, 0x18) == 0) {
                g_CurrentActor->unk_77 = 1;
            } else if (SYS_TestFlag(g_SceneEventFlags, 0x19) == 0) {
                func_801F55F0(1);
                g_CurrentActor->unk_77 = 2;
            } else if (SYS_TestFlag(g_SceneEventFlags, 0x1A) == 0) {
                g_CurrentActor->unk_77 = 3;
            } else {
                g_CurrentActor->unk_77 = 4;
            }
            break;
        case 1:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                member = &g_Game.members[i];
                if (member->pos.x.part.integer >= 0x39 && (u32)(member->pos.y.part.integer - 0x53) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask & BYTE_MASK);
            g_CurrentActor->unk_77 = index + 4;
            break;
        case 2:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                member = &g_Game.members[i];
                if (member->pos.y.part.integer >= 0x3B && (u32)(member->pos.x.part.integer - 0x33) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask & BYTE_MASK);
            func_801F55F0(0);
            g_CurrentActor->unk_77 = index + 4;
            break;
        case 3:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                member = &g_Game.members[i];
                if (member->pos.x.part.integer >= 0x22 && (u32)(member->pos.y.part.integer - 0x41) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask & BYTE_MASK);
            g_CurrentActor->unk_77 = index + 4;
            break;
        case 4:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                member = &g_Game.members[i];
                if (member->pos.y.part.integer < 0x41 && (u32)(member->pos.x.part.integer - 0x1C) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask & BYTE_MASK);
            if (SYS_TestFlag(g_SceneEventFlags, 0x1B)) {
                g_CurrentActor->unk_77 = 9;
            } else {
                g_CurrentActor->unk_77 = 8;
            }
            break;
        case 5:
            return;
    }
    g_CurrentActor->unk_7E = 0;
    D_80147CC8 |= 1;
    Game_SetScriptActive();
    g_SceneEventMode = 12;
    g_SceneEventStep = 0;
    D_801448EE       = 15;
}
#else
INCLUDE_ASM(func_801F4414);
#endif
