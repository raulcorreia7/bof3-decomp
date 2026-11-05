/* Advances the world when the party comes near and updates the area.
 */
/* func_801F2DF4, func_801F2E64 */
MATCH void World_AdvanceAreaWhenPartyNear(void) {
World_AdvanceWhenPartyNear();
    Area_Update(0);
}
