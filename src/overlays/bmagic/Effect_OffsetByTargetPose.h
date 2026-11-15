/* Projects the battle range, then, when the target selector names a party battler, moves the effect screen point by
 * the offset that battler pose and facing pick: FORM_OFFSETS indexed through FORM_KINDS by the dragon form while
 * the battler is in dragon form, else CHARACTER_OFFSETS by its character. Facings 0 and 3 add the x offset, the
 * others subtract it. A statement macro: the member declares PartyMember* work, u32 slot and u8 kind. */
/* func_801EF430 (magic040), func_801EF1B0 (magic042) */
#define EFFECT_OFFSET_BY_TARGET_POSE(FORM_KINDS, FORM_OFFSETS, CHARACTER_OFFSETS)          \
    Battle_ProjectRange();                                                                 \
    slot = LOBU(g_Battle.target_selector);                                                 \
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {                                            \
        if (g_Game.members[slot].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM) { \
            work = g_Task;                                                                 \
            kind = FORM_KINDS[g_Battle.dragon_form];                                       \
            if (work->facing == 0 || work->facing == 3) {                                  \
                work->unk_2E.half += FORM_OFFSETS[kind][work->facing >> 1].x;              \
                work->unk_30.half += FORM_OFFSETS[kind][work->facing >> 1].y;              \
            } else {                                                                       \
                work->unk_2E.half -= FORM_OFFSETS[kind][work->facing >> 1].x;              \
                work->unk_30.half += FORM_OFFSETS[kind][work->facing >> 1].y;              \
            }                                                                              \
        } else {                                                                           \
            work = g_Task;                                                                 \
            kind = g_Game.members[slot].chr.character_id;                                  \
            if (work->facing == 0 || work->facing == 3) {                                  \
                work->unk_2E.half += CHARACTER_OFFSETS[kind][work->facing >> 1].x;         \
                work->unk_30.half += CHARACTER_OFFSETS[kind][work->facing >> 1].y;         \
            } else {                                                                       \
                work->unk_2E.half -= CHARACTER_OFFSETS[kind][work->facing >> 1].x;         \
                work->unk_30.half += CHARACTER_OFFSETS[kind][work->facing >> 1].y;         \
            }                                                                              \
        }                                                                                  \
    }
