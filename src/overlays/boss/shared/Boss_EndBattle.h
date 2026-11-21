/* Runs Battle_ShowActorEntry for battle slots 0 and 1. */
/* func_800C1D50 (boss007), func_800C20B0 (boss013) */
MATCH void Boss_EndBattle(void) {
    Battle_ShowActorEntry(0);
    Battle_ShowActorEntry(1);
}
