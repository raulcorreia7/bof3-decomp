/* Counts the actor wait byte down, reloads it at zero and advances the handler
 * index. One definition shared by the two scenario overlays; every change here
 * must verify every member. */
/* func_801F8730 (scena07), func_801F8D18 (scena08) */
MATCH void Actor_WaitAndStep(Actor* actor) {
    u8 wait;

    wait            = actor->state_02 - 1;
    actor->state_02 = wait;
    if (!(wait & BYTE_MASK)) {
        actor->state_02 = 32;
        actor->unk_01   = actor->unk_01 + 1;
    }
}
