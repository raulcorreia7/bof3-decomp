/* Counts the actor wait byte down, reloads it at zero and advances the handler
 * index. One definition shared by the two scenario overlays; every change here
 * must verify every member. */
/* func_801F8730 (scena07), func_801F8D18 (scena08) */
MATCH void Actor_WaitAndStep(Actor* actor) {
    u8 wait;

    wait        = actor->step - 1;
    actor->step = wait;
    if (!(wait & BYTE_MASK)) {
        actor->step = 32;
        actor->mode = actor->mode + 1;
    }
}
