/* Runs func_8014D978, then Area_SetDrawMode. One definition shared by the area overlays; every change here must
 * verify every member. */
/* func_801F4740 (area016), func_801F4740 (area045), func_801F4740 (area115) */
MATCH void func_801F4740(void) {
    func_8014D978();
    Area_SetDrawMode();
}
