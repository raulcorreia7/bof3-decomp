/* Resets the actor timer and tile class, then advances the handler index. */
/* func_801F3324 (area152), func_801F3394 (area033), func_801F33D0 (area151), func_801F3460 (area016), func_801F3460
   (area045), func_801F3464 (area115), func_801F3478 (area121), func_801F3494 (area087), func_801F3498 (area065),
   func_801F3524 (area104), func_801F3FC4 (area088) */
MATCH void Actor_NextStep(void) {
    SELF(Actor)->timer        = 0;
    SELF(Actor)->param.unk_0B = 0;
    SELF(Actor)->header.mode += 1;
}
