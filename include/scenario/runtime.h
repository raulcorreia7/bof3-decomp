#ifndef SCENARIO_RUNTIME_H
#define SCENARIO_RUNTIME_H

#include "types.h"

/* GAME.EMI runtime functions called by scenario overlays. */
/* The party-selection command returns a status. */

/* Plain braces, not do { } while (0). */
/* Stream in the family, empty the party, join the three members in stream order and restage the party palettes. */
#define SCENE_SET_PARTY(a, b, c)           \
    {                                      \
        EMI_LoadPartyArchives(a, b, c, 0); \
        g_Game.party_size = 0;             \
        Party_JoinMember(a);               \
        Party_JoinMember(b);               \
        Party_JoinMember(c);               \
        Party_LoadPalettes();              \
    }

/* As SCENE_SET_PARTY, without the palette restage. */
#define SCENE_SET_PARTY_NO_RESTAGE(a, b, c) \
    {                                       \
        EMI_LoadPartyArchives(a, b, c, 0);  \
        g_Game.party_size = 0;              \
        Party_JoinMember(a);                \
        Party_JoinMember(b);                \
        Party_JoinMember(c);                \
    }

#endif
