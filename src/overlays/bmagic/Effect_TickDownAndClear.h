/* Count the active battler's effect ticker down and clear the effect work
 * record. One definition shared by the bmagic overlays; every change here must
 * verify every member.
 */
/* Effect_TickDownAndClear (magic012, magic015, magic038, magic045, magic054, magic115), Effect_TickDownAndClear_801EF8A4 (magic045), Effect_TickDownAndClear_801EF888 (magic115) */
/* The statements of Effect_TickDownAndClear. */
#define EFFECT_TICK_DOWN_AND_CLEAR() \
    BMAGIC_TICK_EFFECT_WORK();       \
    func_801E5988()

MATCH void Effect_TickDownAndClear(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
