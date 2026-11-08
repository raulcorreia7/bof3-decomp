/* Raises BATTLE_STATE_WINDOW_BUSY and sets UI mode 4 for a boss battle end hook.
 * One body shared by boss overlays that need different hook names; every change here must
 * verify every member. Kept as a statement macro: the inline form does not match. */
/* Boss_EndBattle2 (boss025 0x800C2B2C), Boss_EndBattle (boss035 0x800C1C3C) */
#define BOSS_SET_END_WINDOW_BODY()                \
    u16* flags;                                   \
    BATTLE_RAISE_STATE(BATTLE_STATE_WINDOW_BUSY); \
    UI_SetMode(4)
