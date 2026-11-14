#ifndef MENU_PARTY_H
#define MENU_PARTY_H

#include "common/vector.h"
#include "types.h"

#define PARTY_FLAGS             0x80144F59u

#define PARTY_FIELD_ORDER_BASE  0x80144F5Au
#define PARTY_BATTLE_ORDER_BASE 0x80144F5Du
#define PARTY_STANDBY           0x801E6244u

#define PARTY_SLOT_COUNT        3
#define FORMATION_COUNT         10

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

/* Swap the bytes two pointers address, as the menu overlays swap two entries of a party order array or of the
 * standby list. */
static inline void Menu_SwapEntries(u8* first, u8* second) {
    u8 temp;

    temp    = *first;
    *first  = *second;
    *second = temp;
}

/* One party formation: its name as the formation menu prints it (the length is what centres it) and the screen
 * offset of each party member from the formation origin. */
typedef struct FormationLayout {
    char    name[7];
    u8      name_length;
    Point2s offsets[PARTY_SLOT_COUNT];
} FormationLayout;

ASSERT_SIZE(FormationLayout, 0x14);
ASSERT_OFFSET(FormationLayout, name_length, 0x07);
ASSERT_OFFSET(FormationLayout, offsets, 0x08);

/* The party members of a formation preview in drawing order, back to front. */
typedef struct FormationOrder {
    u8 members[PARTY_SLOT_COUNT];
} FormationOrder;

/* D_80144F50 */
extern u32 g_Zenny;
/* Stored character id -> character-record slot (Observed:
 * `sel = map[party_order[slot]]`). */

#endif
