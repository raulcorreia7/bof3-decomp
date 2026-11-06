/* Copies the coordinates and height span of the battler D_801EB4E0 into the
 * effect work, clears the effect timer and counter (work bytes 0x09, 0x0A) and
 * advances the effect step (work byte 0x02). One definition shared by the bmagic
 * effect modules; every change here must verify every member. */
/* func_801EF27C (magic056), func_801EEFAC (magic126), Effect_CopyBattlerCoords_801EFAD8 (magic056) */
/* The statements of Effect_CopyBattlerCoords. */
#define BMAGIC_COPY_BATTLER_COORDS()                     \
    do {                                                 \
        PartyBattler* src;                               \
                                                         \
        src                 = (PartyBattler*)D_801EB4E0; \
        g_Task->pos.x       = src->pos.x;                \
        g_Task->pos.y       = src->pos.y;                \
        g_Task->pos.z       = src->pos.z;                \
        g_Task->unk_09      = 0;                         \
        g_Task->timer       = 0;                         \
        g_Task->header.step = g_Task->header.step + 1;   \
    } while (0)

MATCH void Effect_CopyBattlerCoords(void) {
    BMAGIC_COPY_BATTLER_COORDS();
}
