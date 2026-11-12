#include "area108_14.h"

/* Steps the scene event the party leader's answer picks: the cell table row the leader's facing and
 * cell select chooses the branch, the party cells build the scene run and the actor step follows. */
MATCH void func_801F4414(void) {
    u8  facing;
    u8  index;
    u8  i;
    u8  mask;
    u8  step;
    u8* leader;
    u8* active;

    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    leader = &g_Game.members[0].chr.character_id;
    /* FAKE: the leader id's address must stay in a0 for the facing read at -0x71(a0); a plain
     * member load folds to an absolute lui/lbu and grows the body by 4 bytes (0x508 against 0x504). */
    FAKE_OPAQUE(leader);
    if (*leader != CHAR_ID_GARR) {
        return;
    }
    facing = leader[-0x71] & 7;
    for (index = 0; index < 5; index++) {
        if (facing == D_801F636C[index].facing && D_80147B26[0] == D_801F636C[index].x && D_80147B26[2] == D_801F636C[index].y) {
            break;
        }
    }
    switch (index) {
        case 0:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                if (g_Game.members[i].pos.x.part.integer >= 0x28 && (u16)(g_Game.members[i].pos.y.part.integer - 0x53) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask);
            if (!SYS_TestFlag(g_SceneEventFlags, 0x18)) {
                g_CurrentActor->unk_77 = 1;
            } else if (!SYS_TestFlag(g_SceneEventFlags, 0x19)) {
                func_801F55F0(1);
                g_CurrentActor->unk_77 = 2;
            } else if (!SYS_TestFlag(g_SceneEventFlags, 0x1A)) {
                g_CurrentActor->unk_77 = 3;
            } else {
                g_CurrentActor->unk_77 = 4;
            }
            break;
        case 1:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                if (g_Game.members[i].pos.x.part.integer < 0x39 && (u16)(g_Game.members[i].pos.y.part.integer - 0x53) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask);
            step                   = index + 4;
            g_CurrentActor->unk_77 = step;
            break;
        case 2:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                if (g_Game.members[i].pos.y.part.integer >= 0x3B && (u16)(g_Game.members[i].pos.x.part.integer - 0x33) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask);
            func_801F55F0(0);
            step                   = index + 4;
            g_CurrentActor->unk_77 = step;
            break;
        case 3:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                if (g_Game.members[i].pos.x.part.integer >= 0x22 && (u16)(g_Game.members[i].pos.y.part.integer - 0x41) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask);
            step                   = index + 4;
            g_CurrentActor->unk_77 = step;
            break;
        case 4:
            mask = 0;
            for (i = 1; i < g_Game.party_size; i++) {
                if (g_Game.members[i].pos.y.part.integer < 0x41 && (u16)(g_Game.members[i].pos.x.part.integer - 0x1C) < 2) {
                    mask |= 1 << (i - 1);
                }
            }
            func_801BE1B0(mask);
            if (SYS_TestFlag(g_SceneEventFlags, 0x1B)) {
                g_CurrentActor->unk_77 = 9;
            } else {
                g_CurrentActor->unk_77 = 8;
            }
            break;
        case 5:
        default:
            return;
    }
    g_CurrentActor->unk_7E = 0;
    /* FAKE: holds the actor's clear store before the scene-state byte's address load; without the
     * fence the address fills the store's load delay. */
    FAKE_ORDER_FENCE();
    active = &D_80147CC8;
    *active |= 1;
    Game_SetScriptActive();
    g_SceneEventMode = 0xC;
    g_SceneEventStep = 0;
    D_801448EE       = 0xF;
}
