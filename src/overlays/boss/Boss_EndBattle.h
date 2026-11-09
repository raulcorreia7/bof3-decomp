/* Runs func_800AC844 for battle slots 0 and 1. One definition shared by the boss overlays; every change here must
 * verify every member. */
/* func_800C1D50 (boss007), func_800C20B0 (boss013) */
MATCH void Boss_EndBattle(void) {
    func_800AC844(0);
    func_800AC844(1);
}
