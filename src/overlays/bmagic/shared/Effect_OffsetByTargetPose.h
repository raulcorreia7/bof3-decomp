/* Projects the battle range, then, when the target selector names a party battler, moves the effect screen point by
 * the offset that battler pose and facing pick: FORM_OFFSETS indexed through FORM_TYPES by the dragon form while
 * the battler is in dragon form, else CHARACTER_OFFSETS by its character. Facings 0 and 3 add the x offset, the
 * others subtract it. A statement macro: the member declares PartyMember* work, u32 slot and u8 type. */
/* func_801EF430 (magic040), BMagic_BurstFlareOffset (magic042) */
#define EFFECT_OFFSET_BY_TARGET_POSE(FORM_TYPES, FORM_OFFSETS, CHARACTER_OFFSETS)          \
    Battle_ProjectRange();                                                                 \
    slot = LOBU(g_Battle.target_selector);                                                 \
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {                                            \
        if (g_Game.members[slot].u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM) { \
            work = g_Self;                                                                 \
            type = FORM_TYPES[g_Battle.dragon_form];                                       \
            if (work->facing == 0 || work->facing == 3) {                                  \
                work->screen_x.value += FORM_OFFSETS[type][work->facing >> 1].vx;          \
                work->screen_y.value += FORM_OFFSETS[type][work->facing >> 1].vy;          \
            } else {                                                                       \
                work->screen_x.value -= FORM_OFFSETS[type][work->facing >> 1].vx;          \
                work->screen_y.value += FORM_OFFSETS[type][work->facing >> 1].vy;          \
            }                                                                              \
        } else {                                                                           \
            work = g_Self;                                                                 \
            type = g_Game.members[slot].chr.character_id;                                  \
            if (work->facing == 0 || work->facing == 3) {                                  \
                work->screen_x.value += CHARACTER_OFFSETS[type][work->facing >> 1].vx;     \
                work->screen_y.value += CHARACTER_OFFSETS[type][work->facing >> 1].vy;     \
            } else {                                                                       \
                work->screen_x.value -= CHARACTER_OFFSETS[type][work->facing >> 1].vx;     \
                work->screen_y.value += CHARACTER_OFFSETS[type][work->facing >> 1].vy;     \
            }                                                                              \
        }                                                                                  \
    }
