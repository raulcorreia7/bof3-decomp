#include "battle_03.h"

/* picks the auto-target result byte for one enemy slot: dispatches on the global battle mode byte (1 =
 * enemy-state helper, 4 = decide from enemy targeting flags, otherwise read the preset table entry directly).
 */
/* nonmatching unmeasured: tried 55.15% at the control flow: mode switch with case 1, 4 and default, positive-polarity
 * flag chains, func_801E2D90 takes the slot index (branch-delay-slot a0 setup), non-volatile mode byte; falsified:
 * flags-first and kind-index-first load order through locals (44.44), flat kind*20 offset (44.44), a0/v1 pins on flags
 * and targeting_flags (54.81), declaration order and enemy_index + 3 (55.15 unchanged), 20 min random search run (type
 * hacks only). resume: case 4 header: kind index load, flags load into a0, targeting flags into v1, row in v0, index
 * copy in a1 and parameter copy in a2. */
#ifdef NON_MATCHING
NON_MATCHING u8 Battle_PickEnemyTarget(u8 enemy_index) {
    u16 flags;
    u8  targeting_flags;
    u8  index;
    u8  picked;

    index = enemy_index;
    switch (LOBU(g_BattleActionType)) {
        case 1:
            flags = D_801EB6B0[index][0];
            if (flags & 1) {
                picked = func_801E30B8(index);
                if (picked == GAME_NONE) {
                    return func_801E2E30();
                }
                return picked;
            }
            if (flags & 0x10) {
                return func_801E2D90(index);
            }
            return func_801E2E30();
        case 4:
            targeting_flags = D_801CA718[D_801EB726[index][0]][0];
            flags           = D_801EB6B0[index][0];
            if (flags & 1) {
                if (targeting_flags & ABILITY_TARGET_ALL) {
                    if (targeting_flags & ABILITY_TARGET_BOTH_SIDES) {
                        if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                            return 0xC0;
                        }
                    }
                    if (targeting_flags & ABILITY_TARGET_OPPONENT) {
                        return 0x40;
                    }
                    return 0x80;
                }
                if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                    return index + 3;
                }
                if (targeting_flags & ABILITY_TARGET_OPPONENT) {
                    return func_801E2D4C(index);
                }
                if (flags & 0x10) {
                    return func_801E2D90(index);
                }
                return func_801E2E30();
            }
            if (targeting_flags & ABILITY_TARGET_ALL) {
                if (targeting_flags & ABILITY_TARGET_BOTH_SIDES) {
                    if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                        return 0xC0;
                    }
                }
                if (targeting_flags & ABILITY_TARGET_OPPONENT) {
                    return 0x80;
                }
                return 0x40;
            }
            if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                return index + 3;
            }
            if (!(targeting_flags & ABILITY_TARGET_OPPONENT)) {
                return func_801E2CA4();
            }
            if (flags & 0x10) {
                return func_801E2D90(index);
            }
            return func_801E2E30();
        default:
            return D_801EB635[enemy_index][0];
    }
}
#else
INCLUDE_ASM(Battle_PickEnemyTarget);
#endif
