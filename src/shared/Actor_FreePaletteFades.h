/* Frees the two palette fade targets of the actor slot and resets the area
 * work. The statements of Actor_FreePaletteFades; every change here must
 * verify every member. Members: Actor_FreePaletteFades (scena03, area032,
 * area085) and Actor_FreePaletteFades2 (scena03). */
#define ACTOR_FREE_PALETTE_FADES()                        \
    slots = SP_PTR(u8*, 0u);                              \
    GFX_FreePaletteFadeTarget(&g_Actors[slots[0x11][3]]); \
    slots = SP_PTR(u8*, 0u);                              \
    GFX_FreePaletteFadeTarget(&g_Actors[slots[0x11][4]]); \
    Actor_Clear()

MATCH void Actor_FreePaletteFades(void) {
    u8** slots;

    ACTOR_FREE_PALETTE_FADES();
}
