/* Copies the coordinates and height span of the battler D_801EB4E0 into the
 * effect work, clears the effect timer and counter (work bytes 0x09, 0x0A) and
 * advances the effect step (work byte 0x02). One definition shared by the bmagic
 * effect modules; every change here must verify every member. */
/* func_801EF27C (magic056), func_801EEFAC (magic126), Effect_CopyBattlerCoords_801EFAD8 (magic056) */
/* The statements of Effect_CopyBattlerCoords; each member declares src. */
#define BMAGIC_COPY_BATTLER_COORDS()                             \
    src                             = (PartyBattler*)D_801EB4E0; \
    g_SpadWork->coord_x_34          = src->coord_x_34;           \
    g_SpadWork->coord_y_38          = src->coord_y_38;           \
    g_SpadWork->word_3C             = src->word_3C;              \
    g_SpadWork->word_08.byte.unk_09 = 0;                         \
    g_SpadWork->word_08.byte.unk_0A = 0;                         \
    g_SpadWork->unk_02              = g_SpadWork->unk_02 + 1

MATCH void Effect_CopyBattlerCoords(void) {
    PartyBattler* src;

    BMAGIC_COPY_BATTLER_COORDS();
}
