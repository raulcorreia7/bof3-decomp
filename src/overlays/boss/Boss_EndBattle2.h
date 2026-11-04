/* Runs func_800AC934 for battle slots 0, 1 and 2. One definition shared by the boss overlays; every change here must
 * verify every member. */
/* Boss_EndBattle (boss023 0x800C1A10, boss030 0x800C1A84) */
MATCH void Boss_EndBattle(void) {
    func_800AC934(0);
    func_800AC934(1);
    func_800AC934(2);
}
