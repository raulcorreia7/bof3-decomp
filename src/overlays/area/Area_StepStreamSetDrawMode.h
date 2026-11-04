/* Run the work record's delay-counted stream step (func_8014D978), then stage
 * the area draw mode. One definition shared by the area overlays; every change
 * here must verify every member. */
/* func_801F4740 (area016, area045, area115), func_801F4674 (area033), func_801F4778 (area065), func_801F4770 (area087), func_801F52A0 (area088), func_801F4754 (area121), func_801F46AC (area151), func_801F4600 (area152) */
MATCH void Area_StepStreamSetDrawMode(void) {
    func_8014D978();
    Area_SetDrawMode();
}
