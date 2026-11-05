#ifndef SCENARIO_RUNTIME_H
#define SCENARIO_RUNTIME_H

#include "types.h"

/* GAME.EMI runtime functions called by scenario overlays. */
/* func_8019FA28 */
void Game_RequestAreaChange(u16 selection_seed, u32 context_a, u32 context_b, u8 context_kind);
/* The party-selection command returns a status: the retail returns 1 on its three early exits (addiu $v0,$zero,0x1 in
 * the delay slots at 0x801BE22C, 0x801BE2F4 and 0x801BE4C0) and 0 on the normal path (addu $v0,$zero,$zero at
 * 0x801BE51C). */
s32  func_801BE1B0(u32 index);
/* func_801C1400 */
void Party_BuildBattlers(u32 mode);
void func_801C1630(void);
/* func_801C187C */
s32  Party_JoinMember(s32 char_id);
void func_801C1ABC(s32 character_id);
void func_801C1DF0(s32 handler_index);
void func_801C601C(s8 route_index);

/* Stream in the family, empty the party, join the three members in stream order and restage the party palettes. */
#define SCENE_SET_PARTY(a, b, c)            \
    {                                       \
        EMI_LoaderStreamFamily(a, b, c, 0); \
        g_PartySize = 0;                    \
        Party_JoinMember(a);                \
        Party_JoinMember(b);                \
        Party_JoinMember(c);                \
        func_801C1630();                    \
    }

/* As SCENE_SET_PARTY, without the palette restage. */
#define SCENE_SET_PARTY_NO_RESTAGE(a, b, c) \
    {                                       \
        EMI_LoaderStreamFamily(a, b, c, 0); \
        g_PartySize = 0;                    \
        Party_JoinMember(a);                \
        Party_JoinMember(b);                \
        Party_JoinMember(c);                \
    }

#endif
