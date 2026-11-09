/* Frees the two palette fade targets of the actor slot and resets the area work. Members: Actor_FreePaletteFades (scena03, area032, area085) and Actor_FreePaletteFades2 (scena03). */
#define ACTOR_FREE_PALETTE_FADES()                        \
    GFX_FreePaletteFadeTarget(&g_Actors[g_Task->unk_03]); \
    GFX_FreePaletteFadeTarget(&g_Actors[g_Task->unk_04]); \
    Actor_Clear()

MATCH void Actor_FreePaletteFades(void) {
    ACTOR_FREE_PALETTE_FADES();
}
