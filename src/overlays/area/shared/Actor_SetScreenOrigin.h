/* Places the actor screen origin at x 160 and y 80 (not the centre of the 320 by 240 screen). */
/* func_801F32C4 (area152), func_801F3334 (area033), func_801F3370 (area151), func_801F3400 (area016), func_801F3400
   (area045), func_801F3404 (area115), func_801F3418 (area121), func_801F3434 (area087), func_801F3438 (area065),
   func_801F34C4 (area104), func_801F3F64 (area088) */
MATCH void Actor_SetScreenOrigin(void) {
    Actor* actor;

    actor           = SELF(Actor);
    actor->screen_x = 160;
    actor->screen_y = 80;
}
