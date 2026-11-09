/* Frees the two palette fade targets of the actor slot and resets the area work. */
#define ACTOR_FREE_PALETTE_FADES()                        \
    GFX_FreePaletteFadeTarget(&g_Actors[g_Task->unk_03]); \
    GFX_FreePaletteFadeTarget(&g_Actors[g_Task->unk_04]); \
    Actor_Clear()

MATCH void Actor_FreePaletteFades(void) {
    ACTOR_FREE_PALETTE_FADES();
}
