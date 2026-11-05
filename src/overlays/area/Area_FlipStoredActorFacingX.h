/* Turns the actor stored in scratch cell 0x44 to face the other horizontal
 * way: a row facing left (facing 7) faces right (facing 3), any other row
 * faces left. The facing values and their directions come from
 * g_FacingOffsets. One body shared by the members below; every change must
 * verify every member.
 */
/* func_801F35F0 (area095), func_801F3580 (area096) */
MATCH void Area_FlipStoredActorFacingX(void) {
    Actor* actor;

    actor = SP_REF(Actor*, 0x44);
    if (actor->direction_08 == 7) {
        actor->direction_08 = 3;
    } else {
        actor->direction_08 = 7;
    }
}
