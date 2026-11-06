#ifndef SCENARIO_RUNTIME_H
#define SCENARIO_RUNTIME_H

#include "types.h"

/* GAME.EMI runtime functions called by scenario overlays. */
/* The party-selection command returns a status: the retail returns 1 on its three early exits (addiu $v0,$zero,0x1 in
 * the delay slots at 0x801BE22C, 0x801BE2F4 and 0x801BE4C0) and 0 on the normal path (addu $v0,$zero,$zero at
 * 0x801BE51C). */

/* Plain braces, not do { } while (0): with GCC 2.7.2 the do-while moves the `sw ra` save in scena04 and breaks the
   match. */
/* Stream in the family, empty the party, join the three members in stream order and restage the party palettes. */
#define SCENE_SET_PARTY(a, b, c)            \
    {                                       \
        EMI_LoaderStreamFamily(a, b, c, 0); \
        g_PartySize = 0;                    \
        Party_JoinMember(a);                \
        Party_JoinMember(b);                \
        Party_JoinMember(c);                \
        Party_StagePalettes();              \
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
