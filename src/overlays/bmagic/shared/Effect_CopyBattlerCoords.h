/* Copies the coordinates and height span of the g_BattleEffectBattler into the effect work, clears the effect timer and counter (work bytes 0x09, 0x0A) and advances the effect step (work byte 0x02). */
/* func_801EF27C (magic056), func_801EEFAC (magic126), Effect_CopyBattlerCoords2 (magic056) */
/* The statements of Effect_CopyBattlerCoords. */
#define BMAGIC_COPY_BATTLER_COORDS()                                          \
    do {                                                                      \
        PartyMember* src;                                                     \
                                                                              \
        src                            = (PartyMember*)g_BattleEffectBattler; \
        SELF(PartyMember)->pos.x       = src->pos.x;                          \
        SELF(PartyMember)->pos.y       = src->pos.y;                          \
        SELF(PartyMember)->pos.z       = src->pos.z;                          \
        SELF(PartyMember)->unk_09      = 0;                                   \
        SELF(PartyMember)->timer       = 0;                                   \
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;  \
    } while (0)

MATCH void Effect_CopyBattlerCoords(void) {
    BMAGIC_COPY_BATTLER_COORDS();
}
