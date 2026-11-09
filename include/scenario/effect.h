#ifndef SCENARIO_EFFECT_H
#define SCENARIO_EFFECT_H

#include "psx/mem.h"
#include "types.h"
#include "menu/party.h"

#define PARTY_STATE_BASE 0x80140000u

#define PARTY_STATE_PTR  MEM_PTR(volatile PartyState, PARTY_STATE_BASE)

/* Game RAM at 0x80140000 that scenario overlays and battle also write; the
 * party state is the only part modelled here.
 *
 * Only the fields below are modelled. The spans left as pad are
 * not free memory: overlays that map over this base reuse them, e.g.
 * battle/battle/03 func_801D9428 writes the bytes at +0x83C2..+0x83C7 and battle/battle/15
 * func_800A4458 the halfwords at +0x5F1E..+0x5F4E. Read a pad as "not modelled
 * here", never as "unused". */
typedef struct PartyState {
    u8                       pad_0000[0x4f59];
    /* 0x4F59 */ volatile u8 menu_flags; /* sisyou reads it as the master-menu flags byte */
    /* 0x4F5A */ volatile u8
        field_order[PARTY_SLOT_COUNT]; /* party order out of battle, 0xFF = empty (FORMATION_SLOT_EMPTY) */
    /* 0x4F5D */ volatile u8 battle_order[PARTY_SLOT_COUNT]; /* party order in battle, 0xFF = empty */
    u8                       pad_4F60[0x6254 - 0x4f60];
    /* 0x6254 */ volatile u8
        party_count; /* func_801667A4 appends to both order arrays at this index while it is below PARTY_SLOT_COUNT */
} PartyState;

ASSERT_SIZE(PartyState, 0x6255);

/* The party bytes agree with the addresses menu/party.h owns. */
ASSERT_OFFSET(PartyState, menu_flags, PARTY_FLAGS - PARTY_STATE_BASE);
ASSERT_OFFSET(PartyState, field_order, PARTY_FIELD_ORDER_BASE - PARTY_STATE_BASE);
ASSERT_OFFSET(PartyState, battle_order, PARTY_BATTLE_ORDER_BASE - PARTY_STATE_BASE);

#endif
