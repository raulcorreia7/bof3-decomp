#ifndef MENU_PARTY_H
#define MENU_PARTY_H

#include "types.h"

#define PARTY_FORMATION     0x80144F58u
#define PARTY_FLAGS         0x80144F59u

#define PARTY_ORDER_WALKING 0x80144F5Au
#define PARTY_ORDER_BATTLE  0x80144F5Du
#define PARTY_STANDBY       0x801E6244u

#define PARTY_SLOT_COUNT    3

/*
 * Party ordering, formation, standby, and zenny.
 *
 * The order arrays hold CHAR_ID_* values, not record slots; resolve one
 * through the map below before indexing the 0xA4 character records. See
 * @source: wiki:data/records#character-and-master-data.
 *
 * The byte at 0x80144F58 has two readings: front-end code uses it as the
 * formation index, battle/battle/15 as a menu mode. The address stays; the two
 * meanings stay separate.
 */

/* The statements of Menu_SwapBytes: swap the bytes two pointers address, as the
 * menu overlays swap two entries of a party order array or of the standby list.
 * The member declares `u8 temp`. */
#define MENU_SWAP_BYTES(first, second) \
    temp      = *(first);              \
    *(first)  = *(second);             \
    *(second) = temp

/* D_80144F50 */
extern u32 g_Zenny;
/* Stored character id -> character-record slot (Observed:
 * `sel = map[party_order[slot]]`). */

#endif
