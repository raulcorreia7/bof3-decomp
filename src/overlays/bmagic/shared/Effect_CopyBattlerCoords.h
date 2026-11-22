/* Copies the coordinates and height span of the g_BattleEffectBattler into the effect work, clears the effect timer and counter (work bytes 0x09, 0x0A) and advances the effect step (work byte 0x02). */
/* func_801EF27C (magic056), func_801EEFAC (magic126), Effect_CopyBattlerCoords2 (magic056) */
/* The statements of Effect_CopyBattlerCoords. */
#define BMAGIC_COPY_BATTLER_COORDS()                                    \
    do {                                                                \
        PartyMember* src;                                               \
                                                                        \
        src                      = (PartyMember*)g_BattleEffectBattler; \
        BMAGIC_WORK->pos.x       = src->pos.x;                          \
        BMAGIC_WORK->pos.y       = src->pos.y;                          \
        BMAGIC_WORK->pos.z       = src->pos.z;                          \
        BMAGIC_WORK->unk_09      = 0;                                   \
        BMAGIC_WORK->timer       = 0;                                   \
        BMAGIC_WORK->header.step = BMAGIC_WORK->header.step + 1;        \
    } while (0)

MATCH void Effect_CopyBattlerCoords(void) {
    BMAGIC_COPY_BATTLER_COORDS();
}
